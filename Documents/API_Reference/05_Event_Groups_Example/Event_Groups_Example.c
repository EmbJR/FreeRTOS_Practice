/* FreeRTOS Event Groups Example
 * Demonstrates: xEventGroupCreate, xEventGroupSetBits,
 * xEventGroupClearBits, xEventGroupWaitBits,
 * xEventGroupSync, xEventGroupGetBits,
 * xEventGroupClearBitsFromISR, xEventGroupSetBitsFromISR
 */

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "stdio.h"

// Event group handle
EventGroupHandle_t event_group;

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Task handles
TaskHandle_t task1_handle = NULL;
TaskHandle_t task2_handle = NULL;
TaskHandle_t task3_handle = NULL;

// Event bit definitions
#define BIT_0 (1UL << 0)
#define BIT_1 (1UL << 1)
#define BIT_2 (1UL << 2)
#define BIT_ALL (BIT_0 | BIT_1 | BIT_2)

// Task 1 - sets bits and waits
void vTask1(void *pvParameters) {
    while(1) {
        // Set BIT_0 after 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
        xEventGroupSetBits(event_group, BIT_0);
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Task 1: Set BIT_0\n");
        xSemaphoreGive(printf_mutex);
        
        // Wait for BIT_1 and BIT_2
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Task 1: Waiting for BIT_1 and BIT_2\n");
        xSemaphoreGive(printf_mutex);
        
        EventBits_t bits = xEventGroupWaitBits(
            event_group,
            (BIT_1 | BIT_2),   // Bits to wait for
            pdTRUE,            // Clear bits on exit
            pdTRUE,            // Wait for all bits
            portMAX_DELAY      // Timeout
        );
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Task 1: Received bits 0x%08x\n", (unsigned int)bits);
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Task 2 - sets bits and syncs
void vTask2(void *pvParameters) {
    while(1) {
        // Set BIT_1 after 2 seconds
        vTaskDelay(pdMS_TO_TICKS(2000));
        xEventGroupSetBits(event_group, BIT_1);
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Task 2: Set BIT_1\n");
        xSemaphoreGive(printf_mutex);
        
        // Sync all bits
        EventBits_t bits = xEventGroupSync(
            event_group,
            BIT_2,           // Bits to set
            BIT_ALL,         // Bits to wait for
            portMAX_DELAY    // Timeout
        );
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Task 2: Sync complete, bits = 0x%08x\n", (unsigned int)bits);
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

// Task 3 - sets bits and clears
void vTask3(void *pvParameters) {
    while(1) {
        // Set BIT_2 after 3 seconds
        vTaskDelay(pdMS_TO_TICKS(3000));
        xEventGroupSetBits(event_group, BIT_2);
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Task 3: Set BIT_2\n");
        xSemaphoreGive(printf_mutex);
        
        // Clear BIT_0 after some time
        vTaskDelay(pdMS_TO_TICKS(1000));
        xEventGroupClearBits(event_group, BIT_0);
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Task 3: Cleared BIT_0\n");
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(4000));
    }
}

// Static event group buffer
StaticEventGroup_t xEventGroupBuffer;

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Additional task for static creation demonstration
void vStaticEventGroupTask(void *pvParameters) {
    // Create event group statically
    EventGroupHandle_t xStaticEventGroup = xEventGroupCreateStatic(&xEventGroupBuffer);
    
    if (xStaticEventGroup != NULL) {
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Static event group created successfully\n");
        xSemaphoreGive(printf_mutex);
        
        // Use it
        xEventGroupSetBits(xStaticEventGroup, BIT_0);
        vEventGroupDelete(xStaticEventGroup);
    }
    
    vTaskDelay(pdMS_TO_TICKS(5000));
}

// Task demonstrating ISR event group operations
void vISRTask(void *pvParameters) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    while(1) {
        // Simulate setting bits from ISR
        xEventGroupSetBitsFromISR(event_group, BIT_0, &xHigherPriorityTaskWoken);
        
        if (xHigherPriorityTaskWoken != pdFALSE) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
        
        // Simulate clearing bits from ISR
        xEventGroupClearBitsFromISR(event_group, BIT_1);
        
        // Get bits from ISR context
        EventBits_t bits = xEventGroupGetBitsFromISR(event_group);
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("ISR Event Task: Bits from ISR: 0x%08x\n", (unsigned int)bits);
        xSemaphoreGive(printf_mutex);
        
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
    
    // Create event group
    event_group = xEventGroupCreate();
    if (event_group == NULL) {
        while(1);
    }
    
    // Create tasks
    xTaskCreate(vTask1, "Task1", configMINIMAL_STACK_SIZE, NULL, 1, &task1_handle);
    xTaskCreate(vTask2, "Task2", configMINIMAL_STACK_SIZE, NULL, 2, &task2_handle);
    xTaskCreate(vTask3, "Task3", configMINIMAL_STACK_SIZE, NULL, 3, &task3_handle);
    xTaskCreate(vStaticEventGroupTask, "StaticEvt", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vISRTask, "ISRTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    
    // Start scheduler
    vTaskStartScheduler();
    
    while(1);
    return 0;
}