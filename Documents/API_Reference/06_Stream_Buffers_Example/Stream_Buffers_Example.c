/* FreeRTOS Stream Buffers Example
 * Demonstrates: xStreamBufferCreate, xStreamBufferSend,
 * xStreamBufferReceive, xStreamBufferSpacesAvailable,
 * xStreamBufferBytesAvailable, xStreamBufferSendFromISR,
 * xStreamBufferReceiveFromISR, xStreamBufferSetTriggerLevel,
 * xStreamBufferIsEmpty, xStreamBufferIsFull, xStreamBufferReset
 */

#include "FreeRTOS.h"
#include "task.h"
#include "stream_buffer.h"
#include "stdio.h"

// Stream buffer handle
StreamBufferHandle_t stream_buffer;

// Task handles
TaskHandle_t producer_task_handle = NULL;
TaskHandle_t consumer_task_handle = NULL;

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Producer task
void vProducerTask(void *pvParameters) {
    uint32_t data = 0;
    size_t bytes_available;
    
    while(1) {
        // Send data to stream buffer
        size_t bytes_sent = xStreamBufferSend(
            stream_buffer,
            &data,
            sizeof(data),
            pdMS_TO_TICKS(100)
        );
        
        if (bytes_sent > 0) {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Producer: Sent %u (%u bytes)\n", data, (unsigned int)bytes_sent);
            xSemaphoreGive(printf_mutex);
            data++;
        } else {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Producer: Buffer full, data not sent\n");
            xSemaphoreGive(printf_mutex);
        }
        
        // Check available space
        bytes_available = xStreamBufferSpacesAvailable(stream_buffer);
        
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// Consumer task
void vConsumerTask(void *pvParameters) {
    uint32_t received_data;
    size_t bytes_received;
    
    while(1) {
        // Receive data from stream buffer
        bytes_received = xStreamBufferReceive(
            stream_buffer,
            &received_data,
            sizeof(received_data),
            pdMS_TO_TICKS(1000)  // Timeout
        );
        
        if (bytes_received > 0) {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Consumer: Received %u (%u bytes)\n", received_data, (unsigned int)bytes_received);
            xSemaphoreGive(printf_mutex);
        } else {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Consumer: No data received\n");
            xSemaphoreGive(printf_mutex);
        }
        
        // Check buffer status
        if (xStreamBufferIsEmpty(stream_buffer) != pdFALSE) {
            // Buffer is empty
        }
        
        if (xStreamBufferIsFull(stream_buffer) != pdFALSE) {
            // Buffer is full
        }
        
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

// Static memory for stream buffer
uint8_t ucStreamBufferStorageArea[100];
StaticStreamBuffer_t xStaticStreamBuffer;

// Additional task for static stream buffer demonstration
void vStaticStreamBufferTask(void *pvParameters) {
    // Create stream buffer statically
    StreamBufferHandle_t xStaticBuffer = xStreamBufferCreateStatic(
        100,
        10,
        ucStreamBufferStorageArea,
        &xStaticStreamBuffer
    );
    
    if (xStaticBuffer != NULL) {
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Static stream buffer created\n");
        xSemaphoreGive(printf_mutex);
        
        // Use it
        uint32_t data = 0x12345678;
        size_t bytes_sent = xStreamBufferSend(xStaticBuffer, &data, sizeof(data), 0);
        
        if (bytes_sent > 0) {
            uint32_t received;
            bytes_sent = xStreamBufferReceive(xStaticBuffer, &received, sizeof(received), 0);
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Static buffer: sent 0x%08x, received 0x%08x\n", data, received);
            xSemaphoreGive(printf_mutex);
        }
        
        vStreamBufferDelete(xStaticBuffer);
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
    
    // Create stream buffer (buffer size = 100 bytes, trigger level = 1 byte)
    stream_buffer = xStreamBufferCreate(100, 1);
    if (stream_buffer == NULL) {
        while(1);
    }
    
    // Set trigger level
    xStreamBufferSetTriggerLevel(stream_buffer, 10);
    
    // Create tasks
    xTaskCreate(vProducerTask, "Producer", configMINIMAL_STACK_SIZE, NULL, 1, &producer_task_handle);
    xTaskCreate(vConsumerTask, "Consumer", configMINIMAL_STACK_SIZE, NULL, 2, &consumer_task_handle);
    xTaskCreate(vStaticStreamBufferTask, "StaticStream", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    
    // Start scheduler
    vTaskStartScheduler();
    
    while(1);
    return 0;
}