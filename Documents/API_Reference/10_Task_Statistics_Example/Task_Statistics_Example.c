/* FreeRTOS Task Statistics Example
 * Demonstrates: vTaskGetInfo, uxTaskGetStackHighWaterMark,
 * eTaskGetState, uxTaskGetSystemState, vTaskGetRunTimeStats,
 * pcTaskGetName, uxTaskGetNumberOfTasks, vTaskList
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio.h"

// Task handles
TaskHandle_t task1_handle = NULL;
TaskHandle_t task2_handle = NULL;
TaskHandle_t task3_handle = NULL;

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Task that provides statistics
void vStatsTask(void *pvParameters) {
    TaskStatus_t *pxTaskStatusArray;
    UBaseType_t uxArraySize;
    uint32_t ulTotalRunTime;
    char cBuffer[1000];
    
    while(1) {
        // Get number of tasks
        UBaseType_t uxTasks = uxTaskGetNumberOfTasks();
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Number of tasks: %u\n", uxTasks);
        xSemaphoreGive(printf_mutex);
        
        // Get task list (simplified)
        // In real application, you'd need a buffer for vTaskList
        // vTaskList(cBuffer);
        
        // Get run time stats
        vTaskGetRunTimeStats(cBuffer);
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Run time stats:\n%s\n", cBuffer);
        xSemaphoreGive(printf_mutex);
        
        // Get system state
        uxArraySize = uxTasks;
        pxTaskStatusArray = pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));
        
        if (pxTaskStatusArray != NULL) {
            uxArraySize = uxTaskGetSystemState(pxTaskStatusArray, uxArraySize, &ulTotalRunTime);
            
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("System state:\n");
            for (UBaseType_t x = 0; x < uxArraySize; x++) {
                printf("Task: %s, State: %u, Priority: %u, Stack HighWater: %u\n",
                    pxTaskStatusArray[x].pcTaskName,
                    (unsigned int)pxTaskStatusArray[x].eCurrentState,
                    (unsigned int)pxTaskStatusArray[x].uxCurrentPriority,
                    (unsigned int)pxTaskStatusArray[x].usStackHighWaterMark);
            }
            printf("Total run time: %u\n", (unsigned int)ulTotalRunTime);
            xSemaphoreGive(printf_mutex);
            
            vPortFree(pxTaskStatusArray);
        }
        
        // Get individual task info
        TaskStatus_t xTaskStatus;
        vTaskGetInfo(task1_handle, &xTaskStatus, pdTRUE, eBlocked);
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Task 1 info: State=%u, Priority=%u, StackWater=%u\n",
            (unsigned int)xTaskStatus.eCurrentState,
            (unsigned int)xTaskStatus.uxCurrentPriority,
            (unsigned int)xTaskStatus.usStackHighWaterMark);
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

// Sample tasks for statistics
void vTask1(void *pvParameters) {
    while(1) {
        // Simulate work
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vTask2(void *pvParameters) {
    while(1) {
        // Simulate work
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void vTask3(void *pvParameters) {
    while(1) {
        // Simulate work
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
    xTaskCreate(vTask1, "Task1", configMINIMAL_STACK_SIZE, NULL, 1, &task1_handle);
    xTaskCreate(vTask2, "Task2", configMINIMAL_STACK_SIZE, NULL, 2, &task2_handle);
    xTaskCreate(vTask3, "Task3", configMINIMAL_STACK_SIZE, NULL, 3, &task3_handle);
    
    // Create statistics task
    xTaskCreate(vStatsTask, "Stats", configMINIMAL_STACK_SIZE, NULL, 4, NULL);
    
    // Start scheduler
    vTaskStartScheduler();
    
    while(1);
    return 0;
}