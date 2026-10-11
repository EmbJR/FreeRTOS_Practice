/* FreeRTOS Message Buffers Example
 * Demonstrates: xMessageBufferCreate, xMessageBufferSend,
 * xMessageBufferReceive, xMessageBufferSpacesAvailable,
 * xMessageBufferIsEmpty, xMessageBufferIsFull,
 * xMessageBufferSendFromISR, xMessageBufferReceiveFromISR,
 * xMessageBufferReset
 */

#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"
#include "stdio.h"

// Message buffer handle
MessageBufferHandle_t message_buffer;

// Task handles
TaskHandle_t sender_task_handle = NULL;
TaskHandle_t receiver_task_handle = NULL;

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Sender task
void vSenderTask(void *pvParameters) {
    uint32_t message_id = 0;
    
    while(1) {
        // Prepare message (variable length)
        char message[64];
        snprintf(message, sizeof(message), "Message %u from Sender", (unsigned int)message_id);
        size_t message_len = strlen(message) + 1; // Include null terminator
        
        // Send message to message buffer
        size_t bytes_sent = xMessageBufferSend(
            message_buffer,
            message,
            message_len,
            pdMS_TO_TICKS(100)
        );
        
        if (bytes_sent > 0) {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Sender: Sent message '%s' (%u bytes)\n", message, (unsigned int)bytes_sent);
            xSemaphoreGive(printf_mutex);
            message_id++;
        } else {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Sender: Buffer full, message not sent\n");
            xSemaphoreGive(printf_mutex);
        }
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Receiver task
void vReceiverTask(void *pvParameters) {
    char received_message[128];
    size_t bytes_received;
    
    while(1) {
        // Receive message from buffer
        bytes_received = xMessageBufferReceive(
            message_buffer,
            received_message,
            sizeof(received_message),
            pdMS_TO_TICKS(2000)  // Timeout
        );
        
        if (bytes_received > 0) {
            received_message[bytes_received - 1] = '\0'; // Ensure null termination
            
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Receiver: Received message '%s' (%u bytes)\n", received_message, (unsigned int)bytes_received);
            xSemaphoreGive(printf_mutex);
        } else {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Receiver: No message received (timeout)\n");
            xSemaphoreGive(printf_mutex);
        }
        
        // Check buffer status
        if (xMessageBufferIsEmpty(message_buffer) != pdFALSE) {
            // Buffer is empty
        }
        
        if (xMessageBufferIsFull(message_buffer) != pdFALSE) {
            // Buffer is full
        }
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// Static memory for message buffer
uint8_t ucMessageBufferStorageArea[256];
StaticMessageBuffer_t xStaticMessageBuffer;

// Additional task for static message buffer demonstration
void vStaticMessageBufferTask(void *pvParameters) {
    // Create message buffer statically
    MessageBufferHandle_t xStaticBuffer = xMessageBufferCreateStatic(
        256,
        ucMessageBufferStorageArea,
        &xStaticMessageBuffer
    );
    
    if (xStaticBuffer != NULL) {
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Static message buffer created\n");
        xSemaphoreGive(printf_mutex);
        
        // Use it
        char message[] = "Hello from static buffer";
        size_t bytes_sent = xMessageBufferSend(xStaticBuffer, message, strlen(message) + 1, 0);
        
        if (bytes_sent > 0) {
            char received[64];
            size_t bytes_received = xMessageBufferReceive(xStaticBuffer, received, sizeof(received), 0);
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Static buffer: sent '%s', received '%s'\n", message, received);
            xSemaphoreGive(printf_mutex);
        }
        
        vMessageBufferDelete(xStaticBuffer);
    }
    
    vTaskDelay(pdMS_TO_TICKS(5000));
}

int main(void) {
    // Initialize hardware
    // Board_Init();
    
    printf_mutex = xSemaphoreCreateMutex();
    if (printf_mutex == NULL) {
        while(1);
    }
    
    // Create message buffer (buffer size = 256 bytes)
    message_buffer = xMessageBufferCreate(256);
    if (message_buffer == NULL) {
        while(1);
    }
    
    // Create tasks
    xTaskCreate(vSenderTask, "Sender", configMINIMAL_STACK_SIZE, NULL, 1, &sender_task_handle);
    xTaskCreate(vReceiverTask, "Receiver", configMINIMAL_STACK_SIZE, NULL, 2, &receiver_task_handle);
    xTaskCreate(vStaticMessageBufferTask, "StaticMsg", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    
    // Start scheduler
    vTaskStartScheduler();
    
    while(1);
    return 0;
}