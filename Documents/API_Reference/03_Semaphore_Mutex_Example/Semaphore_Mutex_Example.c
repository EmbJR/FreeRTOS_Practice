/* FreeRTOS Semaphore & Mutex Example
 * Demonstrates: xSemaphoreCreateBinary, xSemaphoreCreateCounting,
 * xSemaphoreCreateMutex, xSemaphoreTake, xSemaphoreGive,
 * xSemaphoreTakeRecursive, xSemaphoreGiveRecursive,
 * xSemaphoreGetMutexHolder, uxSemaphoreGetCount, vSemaphoreDelete
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio.h"

// Semaphore handles
SemaphoreHandle_t binary_semaphore;
SemaphoreHandle_t counting_semaphore;
SemaphoreHandle_t mutex;

// Task handles
TaskHandle_t task1_handle = NULL;
TaskHandle_t task2_handle = NULL;
TaskHandle_t task3_handle = NULL;

// Shared resource
uint32_t shared_resource = 0;

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Task 1 - uses binary semaphore
void vTask1(void *pvParameters) {
    while(1) {
        // Take binary semaphore (initially given)
        if (xSemaphoreTake(binary_semaphore, portMAX_DELAY) == pdPASS) {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Task 1: Got binary semaphore, accessing shared resource\n");
            xSemaphoreGive(printf_mutex);
            
            shared_resource++;
            
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Task 1: Shared resource = %u\n", shared_resource);
            xSemaphoreGive(printf_mutex);
            
            // Give back semaphore
            xSemaphoreGive(binary_semaphore);
        }
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Task 2 - uses counting semaphore
void vTask2(void *pvParameters) {
    uint32_t count;
    
    while(1) {
        // Take counting semaphore (simulating event counting)
        if (xSemaphoreTake(counting_semaphore, portMAX_DELAY) == pdPASS) {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Task 2: Got counting semaphore, count = %u\n", uxSemaphoreGetCount(counting_semaphore));
            xSemaphoreGive(printf_mutex);
        }
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Task demonstrating ISR semaphore operations
void vISRSemaphoreTask(void *pvParameters) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    while(1) {
        // Give semaphore from ISR context simulation
        xSemaphoreGiveFromISR(binary_semaphore, &xHigherPriorityTaskWoken);
        
        if (xHigherPriorityTaskWoken != pdFALSE) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
        
        // Take semaphore from ISR context simulation
        if (xSemaphoreTakeFromISR(binary_semaphore, &xHigherPriorityTaskWoken, pdMS_TO_TICKS(10)) == pdPASS) {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("ISR Semaphore: Took binary semaphore from ISR\n");
            xSemaphoreGive(printf_mutex);
        }
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Static memory buffers for static creation
StaticSemaphore_t xBinarySemaphoreBuffer;
StaticSemaphore_t xCountingSemaphoreBuffer;
StaticSemaphore_t xMutexBuffer;
StaticSemaphore_t xRecursiveMutexBuffer;

// Additional task for ISR demonstration
void vISRSemaphoreTask(void *pvParameters) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    while(1) {
        // Simulate giving semaphore from ISR
        xSemaphoreGiveFromISR(binary_semaphore, &xHigherPriorityTaskWoken);
        
        if (xHigherPriorityTaskWoken != pdFALSE) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
        
        // Simulate taking semaphore from ISR
        if (xSemaphoreTakeFromISR(binary_semaphore, &xHigherPriorityTaskWoken, pdMS_TO_TICKS(10)) == pdPASS) {
            // Taken successfully
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
    
    // Create binary semaphore (dynamic)
    binary_semaphore = xSemaphoreCreateBinary();
    if (binary_semaphore != NULL) {
        xSemaphoreGive(binary_semaphore);
    }
    
    // Create counting semaphore (dynamic)
    counting_semaphore = xSemaphoreCreateCounting(10, 0);
    if (counting_semaphore != NULL) {
        xSemaphoreGive(counting_semaphore);
        xSemaphoreGive(counting_semaphore);
    }
    
    // Create mutex (dynamic)
    mutex = xSemaphoreCreateMutex();
    if (mutex == NULL) {
        while(1);
    }
    
    // Create semaphores using static allocation
    binary_semaphore = xSemaphoreCreateBinaryStatic(&xBinarySemaphoreBuffer);
    if (binary_semaphore != NULL) {
        xSemaphoreGive(binary_semaphore);
    }
    
    counting_semaphore = xSemaphoreCreateCountingStatic(10, 0, &xCountingSemaphoreBuffer);
    if (counting_semaphore != NULL) {
        xSemaphoreGive(counting_semaphore);
        xSemaphoreGive(counting_semaphore);
    }
    
    mutex = xSemaphoreCreateMutexStatic(&xMutexBuffer);
    if (mutex == NULL) {
        while(1);
    }
    
    // Create recursive mutex (static)
    SemaphoreHandle_t recursive_mutex = xSemaphoreCreateRecursiveMutexStatic(&xRecursiveMutexBuffer);
    if (recursive_mutex == NULL) {
        while(1);
    }
    
    // Create tasks
    xTaskCreate(vTask1, "Task1", configMINIMAL_STACK_SIZE, NULL, 1, &task1_handle);
    xTaskCreate(vTask2, "Task2", configMINIMAL_STACK_SIZE, NULL, 2, &task2_handle);
    xTaskCreate(vTask3, "Task3", configMINIMAL_STACK_SIZE, NULL, 3, &task3_handle);
    xTaskCreate(vISRSemaphoreTask, "ISRSem", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    
    // Start scheduler
    vTaskStartScheduler();
    
    while(1);
    return 0;
}