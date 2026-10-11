/* FreeRTOS Advanced Task Utilities Example
 * Demonstrates: xTaskCallApplicationTaskHook, xTaskGetApplicationTaskTag,
 *              vTaskSetApplicationTaskTag, vTaskSetThreadLocalStoragePointer,
 *              pvTaskGetThreadLocalStoragePointer, pcTaskGetName,
 *              xTaskGetHandle, xTaskGetSchedulerState, eTaskGetState,
 *              vTaskGetTaskInfo, uxTaskGetSystemState
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio.h"

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Application hook function
void vAppHookFunction(TaskHandle_t xTask) {
    const char *task_name = pcTaskGetName(xTask);
    xSemaphoreTake(printf_mutex, portMAX_DELAY);
    printf("App Hook: Task %s called application hook\n", task_name);
    xSemaphoreGive(printf_mutex);
}

// Task to demonstrate tag and TLS
void vTagTlsTask(void *pvParameters) {
    // Set task tag
    vTaskSetApplicationTaskTag(NULL, (TaskHookFunction_t)0x12345678);
    
    // Set thread-local storage
    vTaskSetThreadLocalStoragePointer(NULL, 0, (void*)0xABCDABCD);
    vTaskSetThreadLocalStoragePointer(NULL, 1, (void*)0xEFEFEFEF);
    
    while(1) {
        // Get tag
        TaskHookFunction_t tag = (TaskHookFunction_t)xTaskGetApplicationTaskTag(NULL);
        
        // Get TLS
        void *tls0 = pvTaskGetThreadLocalStoragePointer(NULL, 0);
        void *tls1 = pvTaskGetThreadLocalStoragePointer(NULL, 1);
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Tag: 0x%08x, TLS0: 0x%08x, TLS1: 0x%08x\n",
               (unsigned int)tag, (unsigned int)tls0, (unsigned int)tls1);
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Task to demonstrate task name and handle lookup
void vNameHandleTask(void *pvParameters) {
    while(1) {
        // Get current task handle by name
        TaskHandle_t h = xTaskGetHandle("NameHandleTask");
        
        if (h != NULL) {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Found task by name: 0x%08x\n", (unsigned int)h);
            xSemaphoreGive(printf_mutex);
        }
        
        vTaskCallApplicationTaskHook(NULL, vAppHookFunction);
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Task to collect and print system information
void vSystemInfoTask(void *pvParameters) {
    while(1) {
        // Get scheduler state
        eTaskState_t state = eTaskGetState(NULL);
        
        // Get task info
        TaskStatus_t xTaskStatus;
        vTaskGetInfo(NULL, &xTaskStatus, pdTRUE, eReady);
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Scheduler State: %s, Task State: %s\n",
               xTaskGetSchedulerState() == taskSCHEDULER_RUNNING ? "Running" : "Not Running",
               state == eRunning ? "Running" : state == eReady ? "Ready" : "Blocked");
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

int main(void) {
    // Initialize hardware
    // Board_Init();
    
    printf_mutex = xSemaphoreCreateMutex();
    if (printf_mutex == NULL) {
        while(1);
    }
    
    // Create tasks
    xTaskCreate(vTagTlsTask, "TagTls", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vNameHandleTask, "NameHandle", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vSystemInfoTask, "SysInfo", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    
    // Start scheduler
    vTaskStartScheduler();
    
    while(1);
    return 0;
}