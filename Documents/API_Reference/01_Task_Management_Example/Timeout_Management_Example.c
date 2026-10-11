/* FreeRTOS Timeout Management Example
 * Demonstrates: xTaskCheckForTimeOut, vTaskSetTimeOutState
 *              xTaskGetSchedulerState, uxTaskGetStackHighWaterMark
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio.h"

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Task to demonstrate timeout checking
void vTimeoutTask(void *pvParameters) {
    TimeOut_t xTimeOut;
    BaseType_t xIsPositiveTickCount;
    TaskStatus_t xStatus;
    
    while(1) {
        // Set up timeout state
        vTaskSetTimeOutState(&xTimeOut);
        
        // Try to take a semaphore with timeout
        xSemaphoreTake(xSemaphoreCreateCounting(10, 0), pdMS_TO_TICKS(1000));
        
        // Check if we timed out
        xTaskCheckForTimeOut(&xTimeOut, &xIsPositiveTickCount);
        
        if (xIsPositiveTickCount == pdFALSE) {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Timeout Task: Timed out!\n");
            xSemaphoreGive(printf_mutex);
        } else {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Timeout Task: Operation completed within timeout\n");
            xSemaphoreGive(printf_mutex);
        }
        
        // Get task state information
        vTaskGetInfo(NULL, &xStatus, pdTRUE, eRunning);
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Task State: %s, Priority: %u, Stack Watermark: %u\n",
               xStatus.eCurrentState == eRunning ? "Running" : "Other",
               (unsigned int)xStatus.uxCurrentPriority,
               (unsigned int)xStatus.usStackHighWaterMark);
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

int main(void) {
    SemaphoreHandle_t test_sem = xSemaphoreCreateCounting(10, 0);
    
    // Initialize hardware
    // Board_Init();
    
    printf_mutex = xSemaphoreCreateMutex();
    if (printf_mutex == NULL) {
        while(1);
    }
    
    // Create timeout demonstration task
    xTaskCreate(vTimeoutTask, "Timeout", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    
    // Start scheduler
    vTaskStartScheduler();
    
    while(1);
    return 0;
}