/* FreeRTOS Software Timers Example
 * Demonstrates: xTimerCreate, xTimerStart, xTimerStop,
 * xTimerChangePeriod, xTimerDelete, pvTimerGetTimerID,
 * xTimerIsTimerActive, xTimerPendFunctionCall,
 * vTimerSetTimerID, xTimerReset, xTimerGetPeriod,
 * xTimerGetExpiry
 */

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "stdio.h"

// Timer handles
TimerHandle_t periodic_timer;
TimerHandle_t one_shot_timer;
TimerHandle_t auto_reload_timer;

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Timer callback functions
void vPeriodicTimerCallback(TimerHandle_t xTimer) {
    uint32_t timer_id = (uint32_t)pvTimerGetTimerID(xTimer);
    
    xSemaphoreTake(printf_mutex, portMAX_DELAY);
    printf("Periodic timer callback (ID: %u)\n", timer_id);
    xSemaphoreGive(printf_mutex);
}

void vOneShotTimerCallback(TimerHandle_t xTimer) {
    uint32_t timer_id = (uint32_t)pvTimerGetTimerID(xTimer);
    
    xSemaphoreTake(printf_mutex, portMAX_DELAY);
    printf("One-shot timer expired (ID: %u)\n", timer_id);
    xSemaphoreGive(printf_mutex);
}

void vAutoReloadTimerCallback(TimerHandle_t xTimer) {
    uint32_t timer_id = (uint32_t)pvTimerGetTimerID(xTimer);
    
    xSemaphoreTake(printf_mutex, portMAX_DELAY);
    printf("Auto-reload timer tick (ID: %u)\n", timer_id);
    xSemaphoreGive(printf_mutex);
}

// Task to monitor timers
void vTimerMonitorTask(void *pvParameters) {
    while(1) {
        // Check if timers are active
        if (xTimerIsTimerActive(periodic_timer) != pdFALSE) {
            TickType_t period = xTimerGetPeriod(periodic_timer);
            TickType_t expiry = xTimerGetExpiry(periodic_timer);
            
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("Periodic timer: period=%u, expiry=%u\n", (unsigned int)period, (unsigned int)expiry);
            xSemaphoreGive(printf_mutex);
        }
        
        if (xTimerIsTimerActive(one_shot_timer) != pdFALSE) {
            TickType_t expiry = xTimerGetExpiry(one_shot_timer);
            
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
            printf("One-shot timer: expiry=%u\n", (unsigned int)expiry);
            xSemaphoreGive(printf_mutex);
        }
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Static memory buffers for static timer creation
StaticTimer_t xTimerBuffer1;
StaticTimer_t xTimerBuffer2;
StaticTimer_t xTimerBuffer3;

// Timer daemon task handle
TimerHandle_t xTimerDaemonTaskHandle;

// Semaphore for UART
SemaphoreHandle_t printf_mutex = NULL;

// Additional timer callback for static timers
void vStaticTimerCallback(TimerHandle_t xTimer) {
    xSemaphoreTake(printf_mutex, portMAX_DELAY);
    printf("Static timer callback called\n");
    xSemaphoreGive(printf_mutex);
}

// Task demonstrating ISR timer operations
void vISRTimerTask(void *pvParameters) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    while(1) {
        // Simulate timer operations from ISR
        xTimerChangePeriodFromISR(periodic_timer, pdMS_TO_TICKS(200), &xHigherPriorityTaskWoken);
        
        if (xHigherPriorityTaskWoken != pdFALSE) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
        
        // Start timer from ISR
        xTimerStartFromISR(one_shot_timer, &xHigherPriorityTaskWoken);
        
        if (xHigherPriorityTaskWoken != pdFALSE) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
        
        // Stop timer from ISR
        xTimerStopFromISR(auto_reload_timer, &xHigherPriorityTaskWoken);
        
        if (xHigherPriorityTaskWoken != pdFALSE) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
        
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
    
    // Create periodic timer (100ms period, auto-reload, ID=1)
    periodic_timer = xTimerCreate(
        "Periodic", 
        pdMS_TO_TICKS(100),
        pdTRUE, 
        (void*)1, 
        vPeriodicTimerCallback
    );
    
    // Create one-shot timer (500ms, no auto-reload, ID=2)
    one_shot_timer = xTimerCreate(
        "OneShot",
        pdMS_TO_TICKS(500),
        pdFALSE,
        (void*)2,
        vOneShotTimerCallback
    );
    
    // Create auto-reload timer (1000ms, ID=3)
    auto_reload_timer = xTimerCreate(
        "AutoReload",
        pdMS_TO_TICKS(1000),
        pdTRUE,
        (void*)3,
        vAutoReloadTimerCallback
    );
    
    // Create static timers
    TimerHandle_t static_timer = xTimerCreateStatic(
        "StaticTimer",
        pdMS_TO_TICKS(2000),
        pdTRUE,
        (void*)4,
        vStaticTimerCallback,
        &xTimerBuffer1
    );
    
    if (static_timer != NULL) {
        xTimerStart(static_timer, 0);
    }
    
    if ((periodic_timer == NULL) || (one_shot_timer == NULL) || (auto_reload_timer == NULL)) {
        while(1);
    }
    
    // Get timer daemon task handle
    xTimerDaemonTaskHandle = xTimerGetTimerDaemonTaskHandle();
    
    // Start timers
    xTimerStart(periodic_timer, 0);
    xTimerStart(one_shot_timer, 0);
    xTimerStart(auto_reload_timer, 0);
    
    // Create timer monitor task
    xTaskCreate(vTimerMonitorTask, "TimerMonitor", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    
    // Create ISR timer task
    xTaskCreate(vISRTimerTask, "ISRTimer", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    
    // Start scheduler
    vTaskStartScheduler();
    
    while(1);
    return 0;
}