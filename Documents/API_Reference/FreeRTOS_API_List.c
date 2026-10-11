##------------------------------------------------------##
##--------------- Task and Scheduler API --------------##
##------------------------------------------------------##
> FreeRTOS:-
portSWITCH_TO_USER_MODE( void );

xTaskAbortDelay( TickType_t xTicksToWait );
xTaskCallApplicationTaskHook( TaskHandle_t xTask, ApplicationTaskHookFunction_t pxHookFunction );
xTaskCatchUpTicks( void );
xTaskCheckForTimeOut( TimeOut_t * const pxTimeOut, BaseType_t * const pxIsPositiveTickCount );
xTaskCreate( TaskFunction_t pvTaskCode, const char * const pcName, const configSTACK_DEPTH_TYPE uxStackDepth, void *pvParameters, UBaseType_t uxPriority, TaskHandle_t *pxCreatedTask );
xTaskCreateStatic( TaskFunction_t pxTaskCode, const char * const pcName, const uint32_t ulStackDepth, void * const pvParameters, UBaseType_t uxPriority, StackType_t * const puxStackBuffer, StaticTask_t * const pxTaskBuffer );
xTaskCreateRestricted( const TaskParameters * const pxTaskDefinition, StackType_t * const puxStackBuffer, StaticTask_t * const pxTaskBuffer );
vTaskDelay( TickType_t xTicksToDelay );
vTaskDelayUntil( TickType_t * const pxPreviousWakeTime, TickType_t xCycleFrequency );
vTaskDelete( TaskHandle_t xTaskToDelete );
taskDISABLE_INTERRUPTS( void );
taskENABLE_INTERRUPTS( void );
taskENTER_CRITICAL( void );
taskENTER_CRITICAL_FROM_ISR( void );
taskEXIT_CRITICAL( void );
taskEXIT_CRITICAL_FROM_ISR( void );
xTaskGetApplicationTaskTag( TaskHandle_t xTask );
xTaskGetCurrentTaskHandle( void );
xTaskGetIdleTaskHandle( void );
xTaskGetHandle( const char *pcName );
uxTaskGetNumberOfTasks( void );
vTaskGetRunTimeStats( char *pcBuffer );
xTaskGetSchedulerState( void );
uxTaskGetStackHighWaterMark( TaskHandle_t xTask );
eTaskGetState( TaskHandle_t xTask );
uxTaskGetSystemState( TaskStatus_t * const pxTaskStatusList, UBaseType_t uxArraySize, uint32_t *pulTotalRunTime );
vTaskGetTaskInfo( TaskHandle_t xTask, TaskStatus_t *pxTaskStatus, BaseType_t xGetAdditionalInfo, eTaskState eState );
pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTask, BaseType_t xIndex );
pcTaskGetName( TaskHandle_t xTask );
xTaskGetTickCount( void );
xTaskGetTickCountFromISR( void );
vTaskList( char *pcBuffer );
xTaskNotify( TaskHandle_t xTaskToNotify, uint32_t ulValue );
xTaskNotifyAndQuery( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyValue eAction, uint32_t *pulPreviousNotification );
xTaskNotifyAndQueryFromISR( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyValue eAction, uint32_t *pulPreviousNotification, BaseType_t *pxHigherPriorityTaskWoken );
xTaskNotifyFromISR( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyValue eAction, BaseType_t *pxHigherPriorityTaskWoken );
xTaskNotifyGive( TaskHandle_t xTaskToNotify );
vTaskNotifyGiveFromISR( TaskHandle_t xTaskToNotify, BaseType_t *pxHigherPriorityTaskWoken );
xTaskNotifyStateClear( TaskHandle_t xTaskToNotify );
ulTaskNotifyTake( BaseType_t xClearCountOnEntry, TickType_t xTicksToWait );
ulTaskNotifyValueClear( TaskHandle_t xTaskToNotify, uint32_t ulBitsToClear );
xTaskNotifyWait( BaseType_t xClearEntered, BaseType_t xClearExiting, uint32_t *pulNotificationValue, TickType_t xTicksToWait );
uxTaskPriorityGet( TaskHandle_t xTask );
vTaskPrioritySet( TaskHandle_t xTask, UBaseType_t uxNewPriority );
vTaskResume( TaskHandle_t xTaskToResume );
xTaskResumeAll( void );
xTaskResumeFromISR( TaskHandle_t xTaskToResume, BaseType_t *pxHigherPriorityTaskWoken );
vTaskSetApplicationTaskTag( TaskHandle_t xTask, TaskHookFunction_t pxHookFunction );
vTaskSetThreadLocalStoragePointer( TaskHandle_t xTask, BaseType_t xIndex, void *pvValue );
vTaskSetTimeOutState( TimeOut_t * const pxTimeOut );
vTaskStartScheduler( void );
vTaskStepTick( TickType_t xTicksToJump );
vTaskSuspend( TaskHandle_t xTaskToSuspend );
vTaskSuspendAll( void );
taskYIELD( void );

> CMSIS:-
osThreadId_t osThreadNew(osThreadFunc_t func, void *argument, const osThreadAttr_t *attr);
osThreadId_t osThreadCreate(osThreadFunc_t func, void *argument, const osThreadAttr_t *attr); // Deprecated in some versions
void osThreadExit(void);
osStatus_t osThreadSuspend (osThreadId_t thread_id);
osStatus_t osThreadResume (osThreadId_t thread_id);
osStatus_t osThreadSetPriority (osThreadId_t thread_id, osPriority_t priority);
osPriority_t osThreadGetPriority (osThreadId_t thread_id);
osThreadId_t osThreadGetId (void);
osThreadState_t osThreadGetState (osThreadId_t thread_id);
osInfo_t osKernelGetInfo (void);
osKernelState_t osKernelGetState (void);
uint32_t osKernelGetTickCount (void);
uint32_t osKernelGetTickFreq (void);

##------------------------------------------------------##
##---------------------- Queues -----------------------##
##------------------------------------------------------##
> FreeRTOS:-
vQueueAddToRegistry( QueueHandle_t xQueue, const char *pcQueueName );
xQueueAddToSet( QueueSetHandle_t xQueueSet, QueueSetMemberHandle_t xQueue);
xQueueCreate( size_t uxItemSize, size_t uxQueueLength );
xQueueCreateSet( size_t uxQueueSetLength );
xQueueCreateStatic( size_t uxItemSize, size_t uxQueueLength, StackType_t * const puxStackBuffer, StaticQueue_t * const pxQueueBuffer );
vQueueDelete( QueueHandle_t xQueue );
pcQueueGetName( QueueHandle_t xQueue );
xQueueIsQueueEmptyFromISR( QueueHandle_t xQueue );
xQueueIsQueueFullFromISR( QueueHandle_t xQueue );
uxQueueMessagesWaiting( QueueHandle_t xQueue );
uxQueueMessagesWaitingFromISR( QueueHandle_t xQueue );
xQueueOverwrite( QueueHandle_t xQueue, const void *pvItemToQueue );
xQueueOverwriteFromISR( QueueHandle_t xQueue, const void *pvItemToQueue );
xQueuePeek( QueueHandle_t xQueue, void *pvBuffer, TickType_t xTicksToWait );
xQueuePeekFromISR( QueueHandle_t xQueue, void *pvBuffer );
xQueueReceive( QueueHandle_t xQueue, void *pvBuffer, TickType_t xTicksToWait );
xQueueReceiveFromISR( QueueHandle_t xQueue, void *pvBuffer, BaseType_t *pxHigherPriorityTaskWoken );
xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore );
xQueueReset( QueueHandle_t xQueue );
xQueueSelectFromSet( QueueSetHandle_t xQueueSet );
xQueueSelectFromSetFromISR( QueueSetHandle_t xQueueSet );
xQueueSend( QueueHandle_t xQueue, const void *pvItemToQueue, TickType_t xTicksToWait );
xQueueSendToFront( QueueHandle_t xQueue, const void *pvItemToQueue, TickType_t xTicksToWait );
xQueueSendToBack( QueueHandle_t xQueue, const void *pvItemToQueue, TickType_t xTicksToWait );
xQueueSendFromISR( QueueHandle_t xQueue, const void *pvItemToQueue, BaseType_t *pxHigherPriorityTaskWoken );
xQueueSendToBackFromISR( QueueHandle_t xQueue, const void *pvItemToQueue, BaseType_t *pxHigherPriorityTaskWoken );
xQueueSendToFrontFromISR( QueueHandle_t xQueue, const void *pvItemToQueue, BaseType_t *pxHigherPriorityTaskWoken );
uxQueueSpacesAvailable( QueueHandle_t xQueue );

> CMSIS:-
osMessageId_t osMessageQueueNew (uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr);
osStatus_t osMessageQueueDelete (osMessageId_t queue_id);
osStatus_t osMessageQueuePut (osMessageId_t queue_id, const void *msg_ptr, uint8_t priority, uint32_t timeout);
osStatus_t osMessageQueueGet (osMessageId_t queue_id, void *msg_ptr, uint8_t *priority, uint32_t timeout);
osStatus_t osMessageQueueReset (osMessageId_t queue_id);
uint32_t osMessageQueueGetCount (osMessageId_t queue_id);
uint32_t osMessageQueueGetMsgSize (osMessageId_t queue_id);
uint32_t osMessageQueueGetCountMax (osMessageId_t queue_id);
osStatus_t osMessageQueueTryPut (osMessageId_t queue_id, const void *msg_ptr);
osStatus_t osMessageQueueTryGet (osMessageId_t queue_id, void *msg_ptr, uint8_t *priority);

##------------------------------------------------------##
##-------------------- Semaphores ---------------------##
##------------------------------------------------------##
> FreeRTOS:-
vSemaphoreCreateBinary( void );
xSemaphoreCreateBinary( void );
xSemaphoreCreateBinaryStatic( void );
xSemaphoreCreateCounting( UBaseType_t uxMaxCount, UBaseType_t uxInitialCount );
xSemaphoreCreateCountingStatic( UBaseType_t uxMaxCount, UBaseType_t uxInitialCount );
xSemaphoreCreateMutex( void );
xSemaphoreCreateMutexStatic( void );
xSemaphoreCreateRecursiveMutex( void );
xSemaphoreCreateRecursiveMutexStatic( void );
vSemaphoreDelete( SemaphoreHandle_t xSemaphore );
uxSemaphoreGetCount( SemaphoreHandle_t xSemaphore );
xSemaphoreGetMutexHolder( SemaphoreHandle_t xMutex );
xSemaphoreGive( SemaphoreHandle_t xSemaphore );
xSemaphoreGiveFromISR( SemaphoreHandle_t xSemaphore, BaseType_t *pxHigherPriorityTaskWoken );
xSemaphoreGiveRecursive( SemaphoreHandle_t xMutex );
xSemaphoreTake( SemaphoreHandle_t xSemaphore, TickType_t xTicksToWait );
xSemaphoreTakeFromISR( SemaphoreHandle_t xSemaphore, BaseType_t *pxHigherPriorityTaskWoken );
xSemaphoreTakeRecursive( SemaphoreHandle_t xMutex, TickType_t xTicksToWait );

> CMSIS:-
osSemaphoreId_t osSemaphoreNew (uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr);
osStatus_t osSemaphoreAcquire (osSemaphoreId_t semaphore_id, uint32_t timeout);
osStatus_t osSemaphoreRelease (osSemaphoreId_t semaphore_id);
osStatus_t osSemaphoreDelete (osSemaphoreId_t semaphore_id);
osStatus_t osSemaphoreAcquireFromISR (osSemaphoreId_t semaphore_id);
uint32_t osSemaphoreGetCount (osSemaphoreId_t semaphore_id);

##------------------------------------------------------##
##------------------- Software Timers ------------------##
##------------------------------------------------------##
> FreeRTOS:-
xTimerChangePeriod( TimerHandle_t xTimer, TickType_t xNewPeriod, TickType_t xTicksToWait );
xTimerChangePeriodFromISR( TimerHandle_t xTimer, TickType_t xNewPeriod, BaseType_t *pxHigherPriorityTaskWoken );
xTimerCreate( const char * const pcTimerName, TickType_t xTimerPeriodInTicks, UBaseType_t uxAutoReload, void *pvTimerID, TimerCallbackFunction_t pxCallbackFunction );
xTimerCreateStatic( const char * const pcTimerName, TickType_t xTimerPeriodInTicks, UBaseType_t uxAutoReload, void *pvTimerID, TimerCallbackFunction_t pxCallbackFunction, StaticTimer_t *pxTimerBuffer );
xTimerDelete( TimerHandle_t xTimer, TickType_t xTicksToWait );
xTimerGetExpiryTime( TimerHandle_t xTimer );
pcTimerGetName( TimerHandle_t xTimer );
xTimerGetPeriod( TimerHandle_t xTimer );
uxTimerGetReloadMode( TimerHandle_t xTimer );
xTimerGetTimerDaemonTaskHandle( void );
pvTimerGetTimerID( TimerHandle_t xTimer );
xTimerIsTimerActive( TimerHandle_t xTimer );
xTimerPendFunctionCall( PendedFunction_t pxPendableFunction, void *pvParameter1, uint32_t ulParameter2, TickType_t xTicksToWait );
xTimerPendFunctionCallFromISR( PendedFunction_t pxPendableFunction, void *pvParameter1, uint32_t ulParameter2, BaseType_t *pxHigherPriorityTaskWoken );
xTimerReset( TimerHandle_t xTimer, TickType_t xTicksToWait );
xTimerResetFromISR( TimerHandle_t xTimer, BaseType_t *pxHigherPriorityTaskWoken );
vTimerSetTimerID( TimerHandle_t xTimer, void *pvNewID );
xTimerStart( TimerHandle_t xTimer, TickType_t xTicksToWait );
xTimerStartFromISR( TimerHandle_t xTimer, BaseType_t *pxHigherPriorityTaskWoken );
xTimerStop( TimerHandle_t xTimer, TickType_t xTicksToWait );
xTimerStopFromISR( TimerHandle_t xTimer, BaseType_t *pxHigherPriorityTaskWoken );

> CMSIS:-
osTimerId_t osTimerNew (osTimerFunc_t func, osTimerType_t type, const osTimerAttr_t *attr, void *argument);
osStatus_t osTimerStart (osTimerId_t timer_id, uint32_t timeout);
osStatus_t osTimerStop (osTimerId_t timer_id, uint32_t timeout);
osStatus_t osTimerDelete (osTimerId_t timer_id);
osTimerState_t osTimerGetState (osTimerId_t timer_id);
uint32_t osTimerGetExpiry (osTimerId_t timer_id);
uint32_t osTimerGetPeriod (osTimerId_t timer_id);

##------------------------------------------------------##
##------------------- Event Groups --------------------##
##------------------------------------------------------##
> FreeRTOS:-
xEventGroupCreate( void );
xEventGroupCreateStatic( void );
vEventGroupDelete( EventGroupHandle_t xEventGroup );
xEventGroupClearBits( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToClear );
xEventGroupClearBitsFromISR( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToClear );
xEventGroupGetBits( EventGroupHandle_t xEventGroup );
xEventGroupGetBitsFromISR( EventGroupHandle_t xEventGroup );
xEventGroupSetBits( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToSet );
xEventGroupSetBitsFromISR( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToSet );
xEventGroupSync( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToSet, EventBits_t uxBitsToWaitFor, TickType_t xTicksToWait );
xEventGroupWaitBits( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToWaitFor, BaseType_t xClearOnExit, BaseType_t xWaitForAllBits, TickType_t xTicksToWait );

> CMSIS:-
osEventFlagsId_t osEventFlagsNew (const osEventFlagsAttr_t *attr);
osStatus_t osEventFlagsDelete (osEventFlagsId_t ef_id);
osStatus_t osEventFlagsSet (osEventFlagsId_t ef_id, uint32_t flags);
osStatus_t osEventFlagsClear (osEventFlagsId_t ef_id, uint32_t flags);
uint32_t osEventFlagsGet (osEventFlagsId_t ef_id, uint32_t flags, uint32_t timeout);
uint32_t osEventFlagsWait (osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout);
uint32_t osEventFlagsGetState (osEventFlagsId_t ef_id);

##------------------------------------------------------##
##----------------- Stream Buffers --------------------##
##------------------------------------------------------##
> FreeRTOS:-
xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer );
xStreamBufferCreate( size_t xBufferSizeBytes, size_t xTriggerLevelBytes );
xStreamBufferCreateStatic( size_t xBufferSizeBytes, size_t xTriggerLevelBytes, uint8_t *pucStreamBufferStorageArea, StaticStreamBuffer_t *pxStaticStreamBuffer );
vStreamBufferDelete( StreamBufferHandle_t xStreamBuffer );
xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer );
xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer );
xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer, void *pvRxData, size_t xDataLengthBytes, TickType_t xTicksToWait );
xStreamBufferReceiveFromISR( StreamBufferHandle_t xStreamBuffer, void *pvRxData, size_t xDataLengthBytes, BaseType_t *pxHigherPriorityTaskWoken );
xStreamBufferReset( StreamBufferHandle_t xStreamBuffer );
xStreamBufferSend( StreamBufferHandle_t xStreamBuffer, const void *pvTxData, size_t xDataLengthBytes, TickType_t xTicksToWait );
xStreamBufferSendFromISR( StreamBufferHandle_t xStreamBuffer, const void *pvTxData, size_t xDataLengthBytes, BaseType_t *pxHigherPriorityTaskWoken );
xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer, size_t xNewTriggerLevel );
xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer );

> CMSIS:-
No direct equivalent in CMSIS-RTOS v2. (Stream buffers are FreeRTOS-specific)

##------------------------------------------------------##
##----------------- Message Buffers -------------------##
##------------------------------------------------------##
> FreeRTOS:-
xMessageBufferCreate( size_t xBufferSizeBytes );
xMessageBufferCreateStatic( size_t xBufferSizeBytes, uint8_t *pucMessageBufferStorageArea, StaticMessageBuffer_t *pxStaticMessageBuffer );
vMessageBufferDelete( MessageBufferHandle_t xMessageBuffer );
xMessageBufferIsEmpty( MessageBufferHandle_t xMessageBuffer );
xMessageBufferIsFull( MessageBufferHandle_t xMessageBuffer );
xMessageBufferReceive( MessageBufferHandle_t xMessageBuffer, void *pvRxData, size_t xDataLengthBytes, TickType_t xTicksToWait );
xMessageBufferReceiveFromISR( MessageBufferHandle_t xMessageBuffer, void *pvRxData, size_t xDataLengthBytes, BaseType_t *pxHigherPriorityTaskWoken );
xMessageBufferReset( MessageBufferHandle_t xMessageBuffer );
xMessageBufferSend( MessageBufferHandle_t xMessageBuffer, const void *pvTxData, size_t xDataLengthBytes, TickType_t xTicksToWait );
xMessageBufferSendFromISR( MessageBufferHandle_t xMessageBuffer, const void *pvTxData, size_t xDataLengthBytes, BaseType_t *pxHigherPriorityTaskWoken );
xMessageBufferSpacesAvailable( MessageBufferHandle_t xMessageBuffer );

> CMSIS:-
No direct equivalent in CMSIS-RTOS v2. (Message buffers are FreeRTOS-specific)

##------------------------------------------------------##
##---------------- Kernel Configuration ---------------##
##------------------------------------------------------##
> FreeRTOS:-
Configuration constants defined in FreeRTOSConfig.h, such as:
configUSE_PREEMPTION
configUSE_IDLE_HOOK
configUSE_TICK_HOOK
configCPU_CLOCK_HZ
configTICK_RATE_HZ
configMAX_PRIORITIES
configMINIMAL_STACK_SIZE
configTOTAL_HEAP_SIZE
configMAX_TASK_NAME_LEN
configUSE_TRACE_FACILITY
configUSE_16_BIT_TICKS
configIDLE_SHOULD_YIELD
configUSE_MUTEXES
configQUEUE_REGISTRY_SIZE
configCHECK_FOR_STACK_OVERFLOW
configUSE_REENTRANT_MUTEXES
configGENERATE_RUN_TIME_STATS
configUSE_COUNTING_SEMAPHORES
configUSE_ALTERNATIVE_API
configUSE_RECURSIVE_MUTEXES
configUSE_MALLOC_FAILED_HOOK
configCHECK_FOR_STACK_OVERFLOW
configRECORD_STACK_HIGH_ADDRESS
configUSE_TIME_SLICING
configUSE_NEWLIB_REENTRANT
configENABLE_BACKWARD_COMPATIBILITY
configKERNEL_INTERRUPT_PRIORITY
configMAX_SYSCALL_INTERRUPT_PRIORITY
configMAX_SYSCALL_INTERRUPT_PRIORITY

> CMSIS:-
Configuration is typically done through system initialization and CMSIS-core functions, not via a single header file. RTOS features are enabled through compiler flags and system initialization.

(End of API list)