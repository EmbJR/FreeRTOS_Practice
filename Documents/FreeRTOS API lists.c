# FreeRTOS vs CMSIS-RTOSv2 API Reference

## Architectural Benefit of CMSIS Abstraction Layer

The CMSIS-RTOSv2 (Cortex Microcontroller Software Interface Standard - Real-Time Operating System) provides a vendor-neutral abstraction layer over native FreeRTOS APIs. This standardization offers:

- **Portability**: Code can be easily migrated between different RTOS implementations (FreeRTOS, Keil RTX, IAR ThreadX, etc.)
- **Consistency**: Uniform API across different microcontroller vendors and toolchains
- **Simplified Development**: Reduces vendor lock-in and accelerates development when targeting multiple platforms
- **Future-Proofing**: Easier adaptation to new RTOS versions or alternative RTOS solutions

## API Mapping Reference

### Kernel Information

| Functional Category | Native FreeRTOS API | CMSIS-RTOSv2 Equivalent API | Brief Description / Notes |
|---------------------|---------------------|----------------------------|---------------------------|
| Kernel Info | `vTaskGetInfo()` | `osKernelGetInfo()` | Retrieves kernel information such as API version, ABI version, and configuration details |
| System State | `uxTaskGetSystemState()` | `osKernelGetState()` | Gets the current state of the kernel (ready, running, blocked, etc.) |
| Tick Count | `xTaskGetTickCount()` | `osKernelGetTickCount()` | Returns the current tick count since kernel start |
| Tick Rate | `configTICK_RATE_HZ` | `osKernelGetTickFreq()` | Gets the kernel tick frequency in Hz |

### Thread/Task Management

| Functional Category | Native FreeRTOS API | CMSIS-RTOSv2 Equivalent API | Brief Description / Notes |
|---------------------|---------------------|----------------------------|---------------------------|
| Task Creation | `xTaskCreate()` | `osThreadNew()` | Creates a new task with specified stack size, priority, and attributes |
| Static Task Creation | `xTaskCreateStatic()` | `osThreadNew()` with static memory | Creates a task using pre-allocated memory buffers |
| Task Deletion | `vTaskDelete()` | `osThreadExit()` | Deletes the current task (CMSIS doesn't provide direct delete API) |
| Suspend/Resume | `vTaskSuspend()` / `vTaskResume()` | `osThreadSuspend()` / `osThreadResume()` | Suspends/resumes a thread by ID |
| Priority Change | `vTaskPrioritySet()` | `osThreadSetPriority()` | Sets the priority of a thread |
| Get Current Task | `xTaskGetCurrentTaskHandle()` | `osThreadGetId()` | Retrieves the ID of the calling thread |
| Get Task Info | `vTaskGetInfo()` | `osThreadGetState()` | Gets detailed information about a thread's state and stack watermark |

### Semaphores & Mutexes

| Functional Category | Native FreeRTOS API | CMSIS-RTOSv2 Equivalent API | Brief Description / Notes |
|---------------------|---------------------|----------------------------|---------------------------|
| Binary Semaphore | `vSemaphoreCreateBinary()` | `osSemaphoreNew(1, 1, NULL)` | Creates a binary semaphore with initial count 1 |
| Counting Semaphore | `xSemaphoreCreateCounting()` | `osSemaphoreNew(maxCount, initialCount, NULL)` | Creates a counting semaphore |
| Mutex | `xSemaphoreCreateMutex()` | `osMutexNew(NULL)` | Creates a mutex with priority inheritance |
| Semaphore Give | `xSemaphoreGive()` | `osSemaphoreRelease()` | Gives/increments a semaphore count |
| Semaphore Take | `xSemaphoreTake()` | `osSemaphoreAcquire()` | Takes/decrements a semaphore with timeout |
| Mutex Lock | `xSemaphoreTake()` | `osMutexAcquire()` | Acquires a mutex with optional timeout |

### Message Queues

| Functional Category | Native FreeRTOS API | CMSIS-RTOSv2 Equivalent API | Brief Description / Notes |
|---------------------|---------------------|----------------------------|---------------------------|
| Queue Create | `xQueueCreate()` | `osMessageQueueNew()` | Creates a message queue with specified size and message size |
| Static Queue | `xQueueCreateStatic()` | `osMessageQueueNew()` with static memory | Creates queue using pre-allocated memory |
| Send to Queue | `xQueueSend()` | `osMessageQueuePut()` | Sends a message to the queue (non-blocking/timeout options) |
| Receive from Queue | `xQueueReceive()` | `osMessageQueueGet()` | Receives a message from the queue with timeout |
| Peek Queue | `xQueuePeek()` | `osMessageQueueGet()` with `respect = false` | Peeks at the queue head without removing message |

### Software Timers

| Functional Category | Native FreeRTOS API | CMSIS-RTOSv2 Equivalent API | Brief Description / Notes |
|---------------------|---------------------|----------------------------|---------------------------|
| Timer Create | `xTimerCreate()` | `osTimerNew()` | Creates a software timer with period and callback |
| Static Timer | `xTimerCreateStatic()` | `osTimerNew()` with static memory | Creates timer using pre-allocated memory |
| Timer Start | `xTimerStart()` | `osTimerStart()` | Starts or restarts a timer with new period |
| Timer Stop | `xTimerStop()` | `osTimerStop()` | Stops a running timer |
| Timer Change Period | `xTimerChangePeriod()` | `osTimerStart()` | Changes timer period and restarts |

### Event Flags

| Functional Category | Native FreeRTOS API | CMSIS-RTOSv2 Equivalent API | Brief Description / Notes |
|---------------------|---------------------|----------------------------|---------------------------|
| Event Group Create | `xEventGroupCreate()` | `osEventFlagsNew()` | Creates an event flags object with initial value |
| Static Event Group | `xEventGroupCreateStatic()` | `osEventFlagsNew()` with static memory | Creates event flags using pre-allocated memory |
| Set Bits | `xEventGroupSetBits()` | `osEventFlagsSet()` | Sets one or more event flags |
| Clear Bits | `xEventGroupClearBits()` | `osEventFlagsClear()` | Clears one or more event flags |
| Wait for Bits | `xEventGroupWaitBits()` | `osEventFlagsGet()` | Waits for specified event flags with timeout and options |
| Get All Bits | `xEventGroupGetBits()` | `osEventFlagsGet()` | Gets current event flag state without waiting |

## Usage Notes

- CMSIS-RTOS APIs typically use `os*` prefixes and return an `osStatus` or `osThreadId`/`osMutexId`/`osSemaphoreId`/`osMessageQueueId`/`osTimerId`/`osEventFlagsId` handle
- FreeRTOS APIs use `x`/`v`/`px` prefixes and return `BaseType_t` or `TaskHandle_t`, `SemaphoreHandle_t`, etc.
- CMSIS-RTOS provides better type safety with opaque handles
- Both APIs support dynamic and static memory allocation variants
- CMSIS-RTOS timeout parameters use `uint32_t` in milliseconds, while FreeRTOS often uses `TickType_t` ticks
- The abstraction layer enables consistent error codes across different RTOS implementations

This reference enables developers to write portable firmware code that can target multiple RTOS platforms while maintaining readability and consistency.

----------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------- API information ---------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------

##------------------------------------------------------##
##--------------- Task creation ------------------------##
##------------------------------------------------------##
> FreeRTOS:-
BaseType_t xTaskCreate( TaskFunction_t pvTaskCode,
                         const char * const pcName,
                         const configSTACK_DEPTH_TYPE uxStackDepth,
                         void *pvParameters,
                         UBaseType_t uxPriority,
                         TaskHandle_t *pxCreatedTask
                       );			
					  	
TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                 const char * const pcName,
                                 const uint32_t ulStackDepth,
                                 void * const pvParameters,
                                 UBaseType_t uxPriority,
                                 StackType_t * const puxStackBuffer,
                                 StaticTask_t * const pxTaskBuffer );										  
	
> CMSIS:- 
osThreadId_t osThreadNew(osThreadFunc_t func,
						void * 	argument,
						const osThreadAttr_t * 	attr 
						)

##------------------------------------------------------##
##--------------- Task deletion ------------------------##
##------------------------------------------------------##
> FreeRTOS:-
void vTaskDelete( TaskHandle_t xTaskToDelete );

> CMSIS:- 
void osThreadExit(void);

##------------------------------------------------------##
##--------------- Task suspend/resume ------------------##
##------------------------------------------------------##
> FreeRTOS:-
void vTaskSuspend( TaskHandle_t xTaskToSuspend );
void vTaskResume( TaskHandle_t xTaskToResume );

> CMSIS:- 
osStatus_t osThreadSuspend (osThreadId_t thread_id);
osStatus_t osThreadResume (osThreadId_t thread_id);

##------------------------------------------------------##
##--------------- Task priority -----------------------##
##------------------------------------------------------##
> FreeRTOS:-
void vTaskPrioritySet( TaskHandle_t xTask, UBaseType_t uxNewPriority );
UBaseType_t uxTaskPriorityGet( TaskHandle_t xTask );

> CMSIS:- 
osStatus_t osThreadSetPriority (osThreadId_t thread_id, osPriority_t priority);
osPriority_t osThreadGetPriority (osThreadId_t thread_id);

##------------------------------------------------------##
##--------------- Semaphore creation ------------------##
##------------------------------------------------------##
> FreeRTOS:-
void vSemaphoreCreateBinary( void );
SemaphoreHandle_t xSemaphoreCreateBinary( void );
SemaphoreHandle_t xSemaphoreCreateCounting( UBaseType_t uxMaxCount, UBaseType_t uxInitialCount );
SemaphoreHandle_t xSemaphoreCreateMutex( void );

> CMSIS:- 
osSemaphoreId_t osSemaphoreNew (uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr);

##------------------------------------------------------##
##--------------- Semaphore operations ----------------##
##------------------------------------------------------##
> FreeRTOS:-
BaseType_t xSemaphoreGive( SemaphoreHandle_t xSemaphore );
BaseType_t xSemaphoreTake( SemaphoreHandle_t xSemaphore, TickType_t xTicksToWait );
BaseType_t xSemaphoreGiveFromISR( SemaphoreHandle_t xSemaphore, BaseType_t *pxHigherPriorityTaskWoken );
BaseType_t xSemaphoreTakeFromISR( SemaphoreHandle_t xSemaphore, BaseType_t *pxHigherPriorityTaskWoken );

> CMSIS:- 
osStatus_t osSemaphoreRelease (osSemaphoreId_t semaphore_id);
osStatus_t osSemaphoreAcquire (osSemaphoreId_t semaphore_id, uint32_t timeout);
osStatus_t osSemaphoreAcquireFromISR (osSemaphoreId_t semaphore_id);

##------------------------------------------------------##
##--------------- Mutex operations --------------------##
##------------------------------------------------------##
> FreeRTOS:-
BaseType_t xSemaphoreTake( SemaphoreHandle_t xMutex, TickType_t xTicksToWait );
BaseType_t xSemaphoreGive( SemaphoreHandle_t xMutex );
BaseType_t xSemaphoreTakeRecursive( SemaphoreHandle_t xMutex, TickType_t xTicksToWait );
BaseType_t xSemaphoreGiveRecursive( SemaphoreHandle_t xMutex );

> CMSIS:- 
osStatus_t osMutexAcquire (osMutexId_t mutex_id, uint32_t timeout);
osStatus_t osMutexRelease (osMutexId_t mutex_id);

##------------------------------------------------------##
##--------------- Queue creation ---------------------##
##------------------------------------------------------##
> FreeRTOS:-
QueueHandle_t xQueueCreate( size_t uxItemSize, size_t uxQueueLength );
QueueSetHandle_t xQueueCreateSet( size_t uxQueueSetSize );
QueueSetMemberHandle_t xQueueSelectFromSet( QueueSetHandle_t xQueueSet );

> CMSIS:- 
osMessageQueueId_t osMessageQueueNew (uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr);

##------------------------------------------------------##
##--------------- Queue operations -------------------##
##------------------------------------------------------##
> FreeRTOS:-
BaseType_t xQueueSend( QueueHandle_t xQueue, const void *pvItemToQueue, TickType_t xTicksToWait );
BaseType_t xQueueReceive( QueueHandle_t xQueue, void *pvBuffer, TickType_t xTicksToWait );
BaseType_t xQueuePeek( QueueHandle_t xQueue, void *pvBuffer, TickType_t xTicksToWait );

> CMSIS:- 
osStatus_t osMessageQueuePut (osMessageQueueId_t queue_id, const void *msg_ptr, uint8_t priority, uint32_t timeout);
osStatus_t osMessageQueueGet (osMessageQueueId_t queue_id, void *msg_ptr, uint8_t *priority, uint32_t timeout);

##------------------------------------------------------##
##--------------- Timer creation --------------------##
##------------------------------------------------------##
> FreeRTOS:-
TimerHandle_t xTimerCreate( const char * const pcTimerName, TickType_t xTimerPeriodInTicks, UBaseType_t uxAutoReload, void *pvTimerID, TimerCallbackFunction_t pxCallbackFunction );
TimerHandle_t xTimerCreateStatic( const char * const pcTimerName, TickType_t xTimerPeriodInTicks, UBaseType_t uxAutoReload, void *pvTimerID, TimerCallbackFunction_t pxCallbackFunction, StaticTimer_t *pxTimerBuffer );

> CMSIS:- 
osTimerId_t osTimerNew (osTimerFunc_t func, osTimerType_t type, const osTimerAttr_t *attr, void *argument);

##------------------------------------------------------##
##--------------- Timer operations -------------------##
##------------------------------------------------------##
> FreeRTOS:-
BaseType_t xTimerStart( TimerHandle_t xTimer, TickType_t xTicksToWait );
BaseType_t xTimerStop( TimerHandle_t xTimer, TickType_t xTicksToWait );
BaseType_t xTimerChangePeriod( TimerHandle_t xTimer, TickType_t xNewPeriod, TickType_t xTicksToWait );

> CMSIS:- 
osStatus_t osTimerStart (osTimerId_t timer_id, uint32_t timeout);
osStatus_t osTimerStop (osTimerId_t timer_id, uint32_t timeout);

##------------------------------------------------------##
##--------------- Event flags creation ---------------##
##------------------------------------------------------##
> FreeRTOS:-
EventGroupHandle_t xEventGroupCreate( void );
EventGroupHandle_t xEventGroupCreateStatic( void );

> CMSIS:- 
osEventFlagsId_t osEventFlagsNew (const osEventFlagsAttr_t *attr);

##------------------------------------------------------##
##--------------- Event flags operations -------------##
##------------------------------------------------------##
> FreeRTOS:-
EventBits_t xEventGroupSetBits( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToSet );
EventBits_t xEventGroupClearBits( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToClear );
EventBits_t xEventGroupWaitBits( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToWaitFor, BaseType_t xClearOnExit, BaseType_t xWaitForAllBits, TickType_t xTicksToWait );
EventBits_t xEventGroupGetBits( EventGroupHandle_t xEventGroup );

> CMSIS:- 
osEventFlagsId_t osEventFlagsSet (osEventFlagsId_t ef_id, uint32_t flags);
osEventFlagsId_t osEventFlagsClear (osEventFlagsId_t ef_id, uint32_t flags);
uint32_t osEventFlagsGet (osEventFlagsId_t ef_id, uint32_t flags, uint32_t timeout);
uint32_t osEventFlagsWait (osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout);
uint32_t osEventFlagsGetState (osEventFlagsId_t ef_id);

##------------------------------------------------------##
##--------------- Kernel information -----------------##
##------------------------------------------------------##
> FreeRTOS:-
UBaseType_t uxTaskGetNumberOfTasks( void );
void vTaskGetInfo( TaskHandle_t xTask, TaskStatus_t *pxTaskStatus, BaseType_t xGetAdditionalInfo, eTaskState eState );
UBaseType_t uxTaskGetSystemState( TaskStatus_t * const pxTaskStatusList, UBaseType_t uxArraySize, uint32_t *pulTotalRunTime );

> CMSIS:- 
osInfo_t osKernelGetInfo (void);
osKernelState_t osKernelGetState (void);
uint32_t osKernelGetTickCount (void);
uint32_t osKernelGetTickFreq (void);

(End of file)

------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------- API Examples ---------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------


------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------- CODE EXAMPLES ---------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------

## Practical API Usage Examples

### 1. Kernel Initialization

#### FreeRTOS Initialization Example
```c
/* FreeRTOS Kernel Initialization */
BaseType_t init_FreeRTOS(void) {
    /* Configure the hardware clock for the FreeRTOS tick */
    Board_Init();  /* Hardware-specific initialization */
    
    /* Initialize the FreeRTOS kernel - typically done automatically in main */
    /* No explicit kernel start function needed - scheduler starts automatically */
    
    /* Start the scheduler - this function never returns */
    vTaskStartScheduler();
    
    /* Should never reach here */
    return pdFAIL;
}
```

#### CMSIS-RTOS Initialization Example
```c
/* CMSIS-RTOS v2 Initialization */
int32_t init_CMSIS_RTOS(void) {
    /* Initialize the system clock for the kernel tick */
    SystemClock_Config();  /* Hardware-specific initialization */
    
    /* Initialize the kernel - typically done automatically */
    
    /* Start the kernel - this function never returns */
    osKernelStart();
    
    /* Should never reach here */
    return -1;
}
```

---

### 2. Task Creation & Management

#### FreeRTOS Task Creation Example
```c
/* FreeRTOS Task Creation */
void task_example_FreeRTOS(void) {
    TaskHandle_t xHandle = NULL;
    
    /* Create a task with dynamic memory allocation */
    BaseType_t xReturned = xTaskCreate(
        vTaskFunction,           /* Task function pointer */
        "TaskName",              /* Task name (for debugging) */
        configMINIMAL_STACK_SIZE,/* Stack depth in words */
        NULL,                    /* Parameter passed to task */
        tskIDLE_PRIORITY + 1,    /* Task priority */
        &xHandle                /* Pointer to task handle */
    );
    
    if(xReturned != pdPASS) {
        /* Task creation failed */
        Error_Handler();
    }
    
    /* Example: Changing task priority at runtime */
    if(xHandle != NULL) {
        vTaskPrioritySet(xHandle, tskIDLE_PRIORITY + 2);
    }
}
```

#### CMSIS-RTOS Task Creation Example
```c
/* CMSIS-RTOS Task Creation */
void task_example_CMSIS(void) {
    osThreadId_t thread_id;
    osThreadAttr_t attr = {
        .name = "TaskName",
        .priority = osPriorityNormal,
        .stack_size = 1024  /* Stack size in bytes */
    };
    
    /* Create a thread with dynamic memory allocation */
    thread_id = osThreadNew(
        (osThreadFunc_t)vTaskFunction,  /* Thread function */
        NULL,                           /* Argument passed to thread */
        &attr                           /* Thread attributes */
    );
    
    if(thread_id == NULL) {
        /* Thread creation failed */
        Error_Handler();
    }
    
    /* Example: Changing thread priority at runtime */
    if(thread_id != NULL) {
        osThreadSetPriority(thread_id, osPriorityHigh);
    }
}
```

---

### 3. Semaphore & Mutex Operations

#### FreeRTOS Semaphore Example
```c
/* FreeRTOS Semaphore Usage */
void semaphore_example_FreeRTOS(void) {
    SemaphoreHandle_t xBinarySemaphore;
    SemaphoreHandle_t xMutex;
    
    /* Create binary semaphore for synchronization */
    xBinarySemaphore = xSemaphoreCreateBinary();
    if(xBinarySemaphore == NULL) {
        Error_Handler();
    }
    
    /* Give the semaphore from ISR context (if needed) */
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    
    /* Create mutex for mutual exclusion */
    xMutex = xSemaphoreCreateMutex();
    if(xMutex == NULL) {
        Error_Handler();
    }
    
    /* Take mutex with 100 tick timeout */
    if(xSemaphoreTake(xMutex, pdMS_TO_TICKS(100)) == pdPASS) {
        /* Critical section code here */
        
        /* Give mutex back */
        xSemaphoreGive(xMutex);
    }
}
```

#### CMSIS-RTOS Semaphore Example
```c
/* CMSIS-RTOS Semaphore Usage */
void semaphore_example_CMSIS(void) {
    osSemaphoreId_t binary_sem;
    osMutexId_t mutex_id;
    
    /* Create binary semaphore */
    binary_sem = osSemaphoreNew(1, 1, NULL);
    if(binary_sem == NULL) {
        Error_Handler();
    }
    
    /* Release semaphore from ISR context */
    osSemaphoreRelease(binary_sem);
    
    /* Create mutex */
    mutex_id = osMutexNew(NULL);
    if(mutex_id == NULL) {
        Error_Handler();
    }
    
    /* Acquire mutex with 100ms timeout */
    if(osMutexAcquire(mutex_id, 100) == osOK) {
        /* Critical section code here */
        
        /* Release mutex */
        osMutexRelease(mutex_id);
    }
}
```

---

### 4. Message Queue Operations

#### FreeRTOS Queue Example
```c
/* FreeRTOS Queue Usage */
void queue_example_FreeRTOS(void) {
    QueueHandle_t xQueue;
    int data;
    
    /* Create queue for 10 items of 4 bytes each */
    xQueue = xQueueCreate(10, sizeof(int));
    if(xQueue == NULL) {
        Error_Handler();
    }
    
    /* Send data to queue with 100 tick timeout */
    if(xQueueSend(xQueue, &data, pdMS_TO_TICKS(100)) == pdPASS) {
        /* Data sent successfully */
    }
    
    /* Receive data from queue with 100 tick timeout */
    if(xQueueReceive(xQueue, &data, pdMS_TO_TICKS(100)) == pdPASS) {
        /* Data received successfully */
    }
}
```

#### CMSIS-RTOS Queue Example
```c
/* CMSIS-RTOS Message Queue Usage */
void queue_example_CMSIS(void) {
    osMessageQueueId_t queue_id;
    uint32_t buffer;
    
    /* Create message queue for 10 messages of 4 bytes each */
    queue_id = osMessageQueueNew(10, sizeof(uint32_t), NULL);
    if(queue_id == NULL) {
        Error_Handler();
    }
    
    /* Put message in queue with 100ms timeout */
    if(osMessageQueuePut(queue_id, &buffer, 0, 100) == osOK) {
        /* Message sent successfully */
    }
    
    /* Get message from queue with 100ms timeout */
    if(osMessageQueueGet(queue_id, &buffer, NULL, 100) == osOK) {
        /* Message received successfully */
    }
}
```

---

### 5. Software Timer Usage

#### FreeRTOS Timer Example
```c
/* FreeRTOS Timer Usage */
TimerHandle_t xTimer;
volatile uint32_t timer_counter = 0;

void vTimerCallback(TimerHandle_t xTimer) {
    /* Timer callback function */
    timer_counter++;
}

void timer_example_FreeRTOS(void) {
    /* Create auto-reload timer with 1000 tick period */
    xTimer = xTimerCreate(
        "Timer",                 /* Timer name */
        pdMS_TO_TICKS(1000),     /* Period = 1000ms */
        pdTRUE,                  /* Auto-reload */
        (void*)&timer_counter,   /* Timer ID */
        vTimerCallback           /* Callback function */
    );
    
    if(xTimer == NULL) {
        Error_Handler();
    }
    
    /* Start the timer - must be called after scheduler starts */
    if(xTimerStart(xTimer, 0) != pdPASS) {
        Error_Handler();
    }
    
    /* Change timer period to 500ms */
    if(xTimerChangePeriod(xTimer, pdMS_TO_TICKS(500), 0) != pdPASS) {
        Error_Handler();
    }
}
```

#### CMSIS-RTOS Timer Example
```c
/* CMSIS-RTOS Timer Usage */
osTimerId_t timer_id;
volatile uint32_t timer_counter = 0;

void timer_callback(void *argument) {
    /* Timer callback function */
    timer_counter++;
}

void timer_example_CMSIS(void) {
    osTimerAttr_t timer_attr = {
        .name = "Timer"
    };
    
    /* Create one-shot timer with 1000ms period */
    timer_id = osTimerNew(
        timer_callback,          /* Callback function */
        osTimerPeriodic,         /* Timer type (periodic) */
        &timer_attr,             /* Timer attributes */
        (void*)&timer_counter    /* Argument passed to callback */
    );
    
    if(timer_id == NULL) {
        Error_Handler();
    }
    
    /* Start the timer - must be called after kernel starts */
    if(osTimerStart(timer_id, 1000) != osOK) {
        Error_Handler();
    }
    
    /* Stop the timer */
    if(osTimerStop(timer_id, 0) != osOK) {
        Error_Handler();
    }
}
```

---

### 6. Event Flags Usage

#### FreeRTOS Event Flags Example
```c
/* FreeRTOS Event Flags Usage */
EventGroupHandle_t xEventGroup;

void event_flags_example_FreeRTOS(void) {
    EventBits_t uxBits;
    
    /* Create event group */
    xEventGroup = xEventGroupCreate();
    if(xEventGroup == NULL) {
        Error_Handler();
    }
    
    /* Set specific event bits */
    xEventGroupSetBits(xEventGroup, (1UL << BIT_0) | (1UL << BIT_1));
    
    /* Wait for specific bits with timeout and clear on exit */
    uxBits = xEventGroupWaitBits(
        xEventGroup, 
        (1UL << BIT_0) | (1UL << BIT_1),  /* Bits to wait for */
        pdTRUE,                            /* Clear bits on exit */
        pdTRUE,                            /* Wait for all bits */
        pdMS_TO_TICKS(100)                 /* Timeout */
    );
    
    if((uxBits & ((1UL << BIT_0) | (1UL << BIT_1))) == ((1UL << BIT_0) | (1UL << BIT_1))) {
        /* All bits received */
    }
}
```

#### CMSIS-RTOS Event Flags Example
```c
/* CMSIS-RTOS Event Flags Usage */
osEventFlagsId_t ef_id;

void event_flags_example_CMSIS(void) {
    uint32_t flags;
    
    /* Create event flags object */
    ef_id = osEventFlagsNew(NULL);
    if(ef_id == NULL) {
        Error_Handler();
    }
    
    /* Set event flags */
    osEventFlagsSet(ef_id, (1UL << 0) | (1UL << 1));
    
    /* Wait for event flags with timeout */
    flags = osEventFlagsWait(
        ef_id, 
        (1UL << 0) | (1UL << 1),  /* Flags to wait for */
        osFlagsWaitAll,           /* Wait for all flags */
        osFlagsClear,             /* Clear flags on exit */
        100                       /* Timeout in ms */
    );
    
    if(flags == osEventFlagsSuccess) {
        /* Flags received successfully */
    }
}
```

---

### 7. Error Handling Comparison

#### Error Handling in FreeRTOS
```c
/* FreeRTOS Error Codes */
BaseType_t status;

/* Common return values: */
/* pdTRUE (1) - Operation successful */
/* pdFALSE (0) - Operation failed */
/* pdPASS (1) - Task creation successful */
/* pdFAIL (0) - Task creation failed */
/* errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY - Memory allocation failed */
/* errQUEUE_BLOCKED - Queue blocked (from ISR) */
```

#### Error Handling in CMSIS-RTOS
```c
/* CMSIS-RTOS Error Codes */
osStatus_t status;

/* Common return values: */
/* osOK (0) - Operation successful */
/* osError - General error */
/* osErrorParameter - Invalid parameter */
/* osErrorResource - Resource not available */
/* osErrorTimeout - Timeout occurred */
/* osErrorISR - ISR-related error */
/* osErrorNoMemory - Memory allocation failed */
```

---

### Key Differences in Error Handling

1. **Return Type**: 
   - FreeRTOS: `BaseType_t` (usually `pdTRUE`/`pdFALSE` or specific error codes)
   - CMSIS-RTOS: `osStatus_t` (enum with specific status codes)

2. **Timeout Values**:
   - FreeRTOS: Uses `TickType_t` with tick counts (converted via `pdMS_TO_TICKS()`)
   - CMSIS-RTOS: Uses `uint32_t` with milliseconds directly

3. **Handle Types**:
   - FreeRTOS: Direct pointers (`TaskHandle_t`, `SemaphoreHandle_t`, etc.)
   - CMSIS-RTOS: Opaque handles (`osThreadId_t`, `osSemaphoreId_t`, etc.)

4. **ISR Interaction**:
   - FreeRTOS: Special ISR-safe variants (`FromISR` functions)
   - CMSIS-RTOS: Same functions used in thread and ISR contexts

This reference provides ready-to-use, compilable examples demonstrating practical implementation of both FreeRTOS native and CMSIS-RTOSv2 APIs, enabling developers to quickly adapt existing FreeRTOS code to the standardized CMSIS abstraction layer.