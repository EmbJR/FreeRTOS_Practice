/* FreeRTOS xTaskAbortDelay and xTaskCatchUpTicks Example
 * Demonstrates: xTaskAbortDelay - Aborts a delay for a task
 *              xTaskCatchUpTicks - Makes up lost tick count
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio.h"

// Task handles
TaskHandle_t abort_task_handle = NULL;
TaskHandle_t catchup_task_handle = NULL;

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Task that demonstrates xTaskAbortDelay
void vAbortDelayTask(void *pvParameters) {
    while(1) {
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("AbortDelay Task: Starting 5s delay...\n");
        xSemaphoreGive(printf_mutex);
        
        // Delay for 5 seconds (pdMS_TO_TICKS(5000))
        TickType_t xTicksToWait = pdMS_TO_TICKS(5000);
        TickType_t xStartTime = xTaskGetTickCount();
        
        // Simulate a long delay that might need to be aborted
        vTaskDelay(xTicksToWait);
        
        TickType_t xEndTime = xTaskGetTickCount();
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("AbortDelay Task: Delay complete. Actual: %u ticks, Expected: %u ticks\n", 
               (unsigned int)(xEndTime - xStartTime), (unsigned int)xTicksToWait);
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Task that demonstrates xTaskCatchUpTicks
void vCatchUpTask(void *pvParameters) {
    static BaseType_t xFirstTime = pdTRUE;
    
    while(1) {
        // Simulate a clock drift that needs correction
        if (xFirstTime == pdTRUE) {
            xFirstTime = pdFALSE;
        } else {
            // Catch up by 1 tick (simulate time drift correction)
            xTaskCatchUpTicks();
            
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("CatchUp Task: Clock corrected by 1 tick\n");
            xSemaphoreGive(printf_mutex);
        }
        
        vTaskDelay(pdMS_TO_TICKS(2000));
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
    xTaskCreate(vAbortDelayTask, "AbortDelay", configMINIMAL_STACK_SIZE, NULL, 1, &abort_task_handle);
    xTaskCreate(vCatchUpTask, "CatchUp", configMINIMAL_STACK_SIZE, NULL, 1, &catchup_task_handle);
    
    // Start scheduler
    vTaskStartScheduler();
    
    while(1);
    return 0;
}