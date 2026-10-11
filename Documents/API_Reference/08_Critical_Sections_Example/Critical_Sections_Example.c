/* FreeRTOS Critical Sections Example
 * Demonstrates: taskENTER_CRITICAL, taskEXIT_CRITICAL,
 * taskENTER_CRITICAL_FROM_ISR, taskEXIT_CRITICAL_FROM_ISR,
 * taskDISABLE_INTERRUPTS, taskENABLE_INTERRUPTS
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio.h"

// Shared resource
volatile uint32_t shared_counter = 0;

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Task that accesses shared resource without protection
void vTaskUnsafe(void *pvParameters) {
    uint32_t local_counter;
    uint32_t i;
    
    while(1) {
        // Unsafe access - may cause race conditions
        local_counter = shared_counter;
        
        // Simulate some processing
        for(i = 0; i < 1000; i++);
        
        shared_counter = local_counter + 1;
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Unsafe Task: shared_counter = %u\n", shared_counter);
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// Task that accesses shared resource with critical section
void vTaskSafe(void *pvParameters) {
    uint32_t local_counter;
    uint32_t i;
    
    while(1) {
        // Enter critical section
        taskENTER_CRITICAL();
        
        // Safe access - interrupts disabled
        local_counter = shared_counter;
        
        // Simulate some processing
        for(i = 0; i < 1000; i++);
        
        shared_counter = local_counter + 1;
        
        // Exit critical section
        taskEXIT_CRITICAL();
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Safe Task: shared_counter = %u\n", shared_counter);
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// Task that accesses shared resource with ISR-safe critical sections
void vISRTask(void *pvParameters) {
    // Simulate an interrupt service routine
    while(1) {
        // Simulate interrupt entering
        taskENTER_CRITICAL_FROM_ISR();
        shared_counter++;
        taskEXIT_CRITICAL_FROM_ISR();
        
        // Simulate disabling/enabling interrupts
        taskDISABLE_INTERRUPTS();
        // Do something critical with interrupts disabled
        shared_counter++;
        taskENABLE_INTERRUPTS();
        
        vTaskDelay(pdMS_TO_TICKS(200));
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
    xTaskCreate(vTaskUnsafe, "Unsafe", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vTaskSafe, "Safe", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vISRTask, "ISR", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    
    // Start scheduler
    vTaskStartScheduler();
    
    while(1);
    return 0;
}