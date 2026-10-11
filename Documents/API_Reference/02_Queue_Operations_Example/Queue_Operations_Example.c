/* FreeRTOS Queue Operations Example
 * Demonstrates: xQueueCreate, xQueueSend, xQueueReceive, xQueuePeek,
 * uxQueueMessagesWaiting, xQueueCreateSet, xQueueSelectFromSet,
 * xQueueAddToSet, xQueueRemoveFromSet, xQueueReset,
 * xQueueSendToFront, xQueueSendToBack, uxQueueSpacesAvailable
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "stdio.h"

// Define queue parameters
#define QUEUE_LENGTH 5
#define ITEM_SIZE sizeof(uint32_t)

// Queue handles
QueueHandle_t data_queue;
QueueSetHandle_t queue_set;

// Task handles
TaskHandle_t producer_task_handle = NULL;
TaskHandle_t consumer_task_handle = NULL;

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Additional queue operations demonstration
void vQueueManagementTask(void *pvParameters) {
    // Example of vQueueAddToRegistry
    vQueueAddToRegistry(data_queue, "MyQueue");
    
    // Example of pcQueueGetName
    const char *queue_name = pcQueueGetName(data_queue);
    if (queue_name != NULL) {
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Queue name: %s\n", queue_name);
        xSemaphoreGive(printf_mutex);
    }
    
    // Check if queue is empty/full from ISR context simulation
    BaseType_t is_empty = xQueueIsQueueEmptyFromISR(data_queue);
    BaseType_t is_full = xQueueIsQueueFullFromISR(data_queue);
    
    xSemaphoreTake(printf_mutex, portMAX_DELAY);
    printf("Queue empty from ISR context: %s\n", is_empty ? "yes" : "no");
    printf("Queue full from ISR context: %s\n", is_full ? "yes" : "no");
    xSemaphoreGive(printf_mutex);
    
    // Get message counts
    UBaseType_t messages_waiting = uxQueueMessagesWaiting(data_queue);
    UBaseType_t messages_waiting_from_isr = uxQueueMessagesWaitingFromISR(data_queue);
    
    xSemaphoreTake(printf_mutex, portMAX_DELAY);
    printf("Messages waiting: %u, From ISR: %u\n", messages_waiting, messages_waiting_from_isr);
    xSemaphoreGive(printf_mutex);
    
    // Overwrite example (send without blocking)
    uint32_t overwrite_data = 0xDEADBEEF;
    if (xQueueOverwrite(data_queue, &overwrite_data) == pdPASS) {
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Overwrite succeeded\n");
        xSemaphoreGive(printf_mutex);
    }
    
    // Example of xQueueSelectFromSetFromISR
    // (Note: This requires ISR context, so we simulate with a task)
    QueueSetMemberHandle_t selected = xQueueSelectFromSetFromISR(queue_set, NULL);
    
    // Example of xQueueRemoveFromSet
    if (xQueueRemoveFromSet(data_queue, queue_set) == pdPASS) {
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Removed queue from set\n");
        xSemaphoreGive(printf_mutex);
    }
    
    // Re-add to set (for demonstration)
    if (xQueueAddToSet(data_queue, queue_set) == pdPASS) {
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Re-added queue to set\n");
        xSemaphoreGive(printf_mutex);
    }
    
    vTaskDelay(pdMS_TO_TICKS(1000));
}

// Task demonstrating ISR-specific queue operations
void vISRQueueTask(void *pvParameters) {
    uint32_t isr_data = 0xCAFEBABE;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    while(1) {
        // Simulate sending from ISR context
        xQueueSendFromISR(data_queue, &isr_data, &xHigherPriorityTaskWoken);
        
        if (xHigherPriorityTaskWoken != pdFALSE) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
        
        // Simulate receiving from ISR context
        uint32_t received_isr;
        if (xQueueReceiveFromISR(data_queue, &received_isr, &xHigherPriorityTaskWoken) == pdPASS) {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("ISR Task: Received from ISR context: 0x%08x\n", received_isr);
            xSemaphoreGive(printf_mutex);
        }
        
        // Peek from ISR
        if (xQueuePeekFromISR(data_queue, &isr_data) == pdPASS) {
            // Peeked successfully
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
    
    // Create queue
    data_queue = xQueueCreate(QUEUE_LENGTH, ITEM_SIZE);
    if (data_queue == NULL) {
        while(1);
    }
    
    // Create queue set
    queue_set = xQueueCreateSet(1); // Set with 1 member
    if (queue_set == NULL) {
        while(1);
    }
    
    // Add queue to set
    if (xQueueAddToSet(data_queue, queue_set) != pdPASS) {
        while(1);
    }
    
    // Create tasks
    xTaskCreate(vProducerTask, "Producer", configMINIMAL_STACK_SIZE, NULL, 1, &producer_task_handle);
    xTaskCreate(vConsumerTask, "Consumer", configMINIMAL_STACK_SIZE, NULL, 2, &consumer_task_handle);
    xTaskCreate(vQueueManagementTask, "QueueMgr", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vISRQueueTask, "ISRQueue", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    
    // Start scheduler
    vTaskStartScheduler();
    
    while(1);
    return 0;
}