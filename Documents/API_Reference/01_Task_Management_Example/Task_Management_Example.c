/* FreeRTOS Task Management Example
 * Demonstrates: xTaskCreate, vTaskDelete, vTaskSuspend, vTaskResume, 
 * vTaskPrioritySet, uxTaskPriorityGet, xTaskGetCurrentTaskHandle,
 * xTaskGetIdleTaskHandle, uxTaskGetNumberOfTasks, vTaskList,
 * xTaskNotify, xTaskNotifyGive, ulTaskNotifyTake, vTaskSuspendAll,
 * vTaskResumeAll, taskYIELD, xTaskNotifyWait, xTaskGetTickCountFromISR,
 * xTaskCallApplicationTaskHook, xTaskGetApplicationTaskTag,
 * vTaskSetApplicationTaskTag, vTaskSetThreadLocalStoragePointer,
 * pvTaskGetThreadLocalStoragePointer, pcTaskGetName, xTaskGetHandle,
 * xTaskGetSchedulerState, eTaskGetState, vTaskGetTaskInfo,
 * uxTaskGetSystemState, vTaskStepTick, xTaskAbortDelay, xTaskCatchUpTicks,
 * xTaskCheckForTimeOut, vTaskSetTimeOutState, xTaskNotifyAndQuery,
 * xTaskNotifyAndQueryFromISR, xTaskNotifyFromISR, xTaskNotifyStateClear,
 * ulTaskNotifyValueClear, xTaskResumeFromISR
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio.h"

// Task handles
TaskHandle_t task1_handle = NULL;
TaskHandle_t task2_handle = NULL;
TaskHandle_t task3_handle = NULL;
TaskHandle_t task4_handle = NULL;
TaskHandle_t task5_handle = NULL;
TaskHandle_t task6_handle = NULL;

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Application hook function
void vAppHookFunction(TaskHandle_t xTask) {
    const char *task_name = pcTaskGetName(xTask);
    xSemaphoreTake(printf_mutex, portMAX_DELAY);
    printf("App Hook: Task %s called application hook\n", task_name);
    xSemaphoreGive(printf_mutex);
}

// Task 1 - basic operations
void vTask1(void *pvParameters) {
    while(1) {
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Task 1 running, handle: %p\n", (void*)xTaskGetCurrentTaskHandle());
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Task 2 - priority and delete
void vTask2(void *pvParameters) {
    while(1) {
        UBaseType_t priority = uxTaskPriorityGet(NULL);
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Task 2 priority: %u\n", priority);
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(2000));
        
        // Delete self after some time
        vTaskDelete(NULL);
    }
}

// Task 3 - suspend/resume
void vTask3(void *pvParameters) {
    while(1) {
        vTaskSuspend(task2_handle);
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Task 3: Suspended Task 2\n");
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(1000));
        
        vTaskResume(task2_handle);
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Task 3: Resumed Task 2\n");
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Task 4 - notifications with wait
void vTask4(void *pvParameters) {
    uint32_t notification_value;
    BaseType_t result;
    
    while(1) {
        result = xTaskNotifyWait(pdFALSE, BIT_0, &notification_value, pdMS_TO_TICKS(3000));
        
        if (result == pdPASS) {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Task 4: Got notification: %u\n", (unsigned int)notification_value);
            xSemaphoreGive(printf_mutex);
        } else {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Task 4: Notification timeout\n");
            xSemaphoreGive(printf_mutex);
        }
        
        xTaskNotifyWait(pdTRUE, UINT_MAX, NULL, portMAX_DELAY);
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Task 5 - tick count from ISR context
void vTickISRTask(void *pvParameters) {
    while(1) {
        TickType_t xTick = xTaskGetTickCountFromISR();
        
        xSemaphoreTake(printf_mutex, portMAX_DELAY);
        printf("Tick from ISR context: %u\n", (unsigned int)xTick);
        xSemaphoreGive(printf_mutex);
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Task 6 - advanced operations
void vAdvancedTask(void *pvParameters) {
    TimeOut_t xTimeOut;
    BaseType_t xIsPositiveTickCount;
    
    while(1) {
        // Timeout management
        vTaskSetTimeOutState(&xTimeOut);
        xTaskCheckForTimeOut(&xTimeOut, &xIsPositiveTickCount);
        
        // Step tick
        vTaskStepTick(10);
        
        // Advanced notification APIs
        uint32_t ulPrev;
        xTaskNotifyAndQuery(NULL, 0, eSetValue, &ulPrev);
        xTaskNotifyStateClear(NULL);
        ulTaskNotifyValueClear(NULL, 0xFFFFFFFF);
        
        // Tag and TLS
        vTaskSetApplicationTaskTag(NULL, (TaskHookFunction_t)0x12345678);
        vTaskSetThreadLocalStoragePointer(NULL, 0, (void*)0xABCDABCD);
        void *tls = pvTaskGetThreadLocalStoragePointer(NULL, 0);
        
        // Get state info
        eTaskState eState = eTaskGetState(NULL);
        TaskStatus_t xStatus;
        vTaskGetInfo(NULL, &xStatus, pdTRUE, eReady);
        UBaseType_t uxTasks = uxTaskGetNumberOfTasks();
        UBaseType_t uxArraySize = uxTasks;
        TaskStatus_t *pxArray = pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));
        if (pxArray != NULL) {
            uxTaskGetSystemState(pxArray, uxArraySize, NULL);
            vPortFree(pxArray);
        }
        
        // Get scheduler state
        xTaskGetSchedulerState();
        
        // Get task handle by name
        TaskHandle_t h = xTaskGetHandle("AdvancedTask");
        
        // Get task name
        const char *name = pcTaskGetName(NULL);
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Task 7 - demonstrates resume from ISR
void vResumeISRTask(void *pvParameters) {
    BaseType_t xHigherPriorityTaskWoken;
    
    while(1) {
        xTaskResumeFromISR(task1_handle, &xHigherPriorityTaskWoken);
        if (xHigherPriorityTaskWoken != pdFALSE) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void) {
    printf_mutex = xSemaphoreCreateMutex();
    if (printf_mutex == NULL) {
        while(1);
    }
    
    // Create tasks
    xTaskCreate(vTask1, "Task1", configMINIMAL_STACK_SIZE, NULL, 2, &task1_handle);
    xTaskCreate(vTask2, "Task2", configMINIMAL_STACK_SIZE, NULL, 2, &task2_handle);
    xTaskCreate(vTask3, "Task3", configMINIMAL_STACK_SIZE, NULL, 1, &task3_handle);
    xTaskCreate(vTask4, "Task4", configMINIMAL_STACK_SIZE, NULL, 2, &task4_handle);
    xTaskCreate(vTickISRTask, "TickISR", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vAdvancedTask, "AdvancedTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vResumeISRTask, "ResumeISR", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    
    vTaskStartScheduler();
    
    while(1);
    return 0;
}

// Application hook for getting idle task handle
void vApplicationGetIdleTaskHandle(TaskHandle_t *pxIdleTaskHandle) {
    *pxIdleTaskHandle = xTaskGetIdleTaskHandle();
}