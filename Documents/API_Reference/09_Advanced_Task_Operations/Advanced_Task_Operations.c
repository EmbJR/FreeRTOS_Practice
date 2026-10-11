/* FreeRTOS Advanced Task Operations Example
 * Demonstrates: xTaskAbortDelay, xTaskCallApplicationTaskHook,
 * xTaskCatchUpTicks, xTaskCheckForTimeOut, vTaskSetApplicationTaskTag,
 * vTaskSetThreadLocalStoragePointer, vTaskSetTimeOutState,
 * vTaskStepTick, vTaskAllocateMPURegions
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio.h"

// Task handles
TaskHandle_t task1_handle = NULL;
TaskHandle_t task2_handle = NULL;

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Application task hook function
void vApplicationTaskHook(TaskHandle_t xTask) {
    xSemaphoreTake(printf_mutex, portMAX_DELAY);
    printf("Application hook called for task: %s\n", pcTaskGetName(xTask));
    xSemaphoreGive(printf_mutex);
}

// Task 1 - demonstrates advanced operations
void vTask1(void *pvParameters) {
    TimeOut_t xTimeOut;
    UBaseType_t uxOriginalPriority;
    
    while(1) {
        // Set timeout state
        vTaskSetTimeOutState(&xTimeOut);
        
        // Check if we can abort delay
        if (xTaskAbortDelay(NULL) == pdPASS) {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Task 1: Successfully aborted delay\n");
            xSemaphoreGive(printf_mutex);
        }
        
        // Call application hook
        xTaskCallApplicationTaskHook(NULL, vApplicationTaskHook);
        
        // Catch up ticks (simulate clock adjustment)
        vTaskCatchUpTicks();
        
        // Check for timeout
        BaseType_t xIsPositiveTickCount;
        xTaskCheckForTimeOut(&xTimeOut, &xIsPositiveTickCount);
        
        // Set thread-local storage
        vTaskSetThreadLocalStoragePointer(NULL, 0, pvTaskGetThreadLocalStoragePointer(NULL, 0));
        
        // Step tick forward (simulate tick increment)
        vTaskStepTick(10);
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Task 2 - demonstrates MPU regions and priority tagging
void vTask2(void *pvParameters) {
    // Set task tag
    vTaskSetApplicationTaskTag(NULL, (TaskHookFunction_t)0x12345678);
    
    // Get task tag
    TaskHookFunction_t tag = (TaskHookFunction_t)xTaskGetApplicationTaskTag(NULL);
    
    xSemaphoreTake(printf_mutex, portMAX_DELAY);
    printf("Task 2: Task tag = 0x%08x\n", (unsigned int)tag);
    xSemaphoreGive(printf_mutex);
    
    // Allocate MPU regions (if MPU is enabled)
    // vTaskAllocateMPURegions(NULL, NULL); // Actual usage requires MPU setup
    
    vTaskDelay(pdMS_TO_TICKS(2000));
}

int main(void) {
    // Initialize hardware
    // Board_Init();
    
    printf_mutex = xSemaphoreCreateMutex();
    if (printf_mutex == NULL) {
        while(1);
    }
    
    // Create tasks
    xTaskCreate(vTask1, "Advanced", configMINIMAL_STACK_SIZE, NULL, 1, &task1_handle);
    xTaskCreate(vTask2, "MPU", configMINIMAL_STACK_SIZE, NULL, 2, &task2_handle);
    
    // Start scheduler
    vTaskStartScheduler();
    
    while(1);
    return 0;
}