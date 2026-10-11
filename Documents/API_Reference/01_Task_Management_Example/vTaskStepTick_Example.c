/* FreeRTOS vTaskStepTick Example
 * Demonstrates: vTaskStepTick - Advances the tick count by a given number of ticks
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio.h"

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Task to demonstrate vTaskStepTick
void vStepTickTask(void *pvParameters) {
    TickType_t xLastExecutionTime;
    const TickType_t xDelay = pdMS_TO_TICKS(1000);
    
    // Initialize xLastExecutionTime for accurate delay
    xLastExecutionTime = xTaskGetTickCount();
    
    while(1) {
        // Wait for next cycle
        vTaskDelayUntil(&xLastExecutionTime, xDelay);
        
        // Step the tick count forward by 10 ticks
        vTaskStepTick(10);
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("vTaskStepTick: Advanced tick count by 10 ticks. Current tick: %u\n", (unsigned int)xTaskGetTickCount());
        xSemaphoreGive(printf_mutex);
    }
}

int main(void) {
    // Initialize hardware
    // Board_Init();
    
    printf_mutex = xSemaphoreCreateMutex();
    if (printf_mutex == NULL) {
        while(1);
    }
    
    // Create the step tick task
    xTaskCreate(vStepTickTask, "StepTick", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    
    // Start scheduler
    vTaskStartScheduler();
    
    while(1);
    return 0;
}