#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* Hardware specific settings */
#define configCPU_CLOCK_HZ              ( ( unsigned long ) 16000000 ) // Set to your system clock (e.g., 48MHz)
#define configTICK_RATE_HZ              ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES            ( 5 )
#define configMINIMAL_STACK_SIZE        ( ( unsigned short ) 128 )
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 5 * 1024 ) ) // Adjust based on your available RAM
#define configMAX_TASK_NAME_LEN         ( 10 )


/* RTOS behavioral settings */
#define configUSE_PREEMPTION            1
#define configUSE_IDLE_HOOK             1
#define configUSE_TICK_HOOK             0
#define configUSE_16_BIT_TICKS          0
#define configIDLE_SHOULD_YIELD         1
#define configUSE_MUTEXES               1
#define configUSE_RECURSIVE_MUTEXES     1
#define configUSE_COUNTING_SEMAPHORES   1

//#define INCLUDE_xTaskDelayUntil         1
#define INCLUDE_vTaskDelay              1
#define INCLUDE_xTaskGetSchedulerState  1
//-------------- Timer enable ---------------------//
#define configUSE_TIMERS                 0
#define configTIMER_TASK_PRIORITY        (configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH         5
#define configTIMER_TASK_STACK_DEPTH     128
//------------------------------------------------//

/* Memory Allocation */
#define configSUPPORT_STATIC_ALLOCATION     1
#define configSUPPORT_DYNAMIC_ALLOCATION    1

#define configMAX_SYSCALL_INTERRUPT_PRIORITY    5



/* Cortex-M7 specific */
#define __NVIC_PRIO_BITS                	4  // STM32H7 uses 4 bits for priority

//--------------- for debugging -----------------//
//-------- for task statistics start ----------//
//#define configGENERATE_RUN_TIME_STATS 	1
//#define configUSE_TRACE_FACILITY      	1
//#define configUSE_STATS_FORMATTING_FUNCTIONS     1

#if (configGENERATE_RUN_TIME_STATS == 1)
void ConfigureTimerForRunTimeStats(void);
extern volatile uint32_t ulHighFrequencyTimerTicks;

#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() ConfigureTimerForRunTimeStats()
#define portGET_RUN_TIME_COUNTER_VALUE() ulHighFrequencyTimerTicks
#endif
//-------- for task statistics ends ----------//

/* Hook definitions */
#define configCHECK_FOR_STACK_OVERFLOW  	2
#define configUSE_MALLOC_FAILED_HOOK 		1

//-----------------------------------------//

//---------------- For MPU ---------------------//
#define configENABLE_MPU 								1
/* For the MPU_xTaskCreate API */
#define configUSE_MPU_WRAPPERS_V1               		0
#define configTOTAL_MPU_REGIONS 						16
#define configSYSTEM_CALL_STACK_SIZE    				( 128 )
#define configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY		1
#define configENABLE_MPU_WRAPPERS             			1
#define configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS	0
/* Set configENABLE_ACCESS_CONTROL_LIST to 1 to use access control list.
 * See https://freertos.org/a00110.html#configENABLE_ACCESS_CONTROL_LIST for details. */
#define configENABLE_ACCESS_CONTROL_LIST				( 1 )
/* See https://freertos.org/a00110.html#configPROTECTED_KERNEL_OBJECT_POOL_SIZE for details. */
#define configPROTECTED_KERNEL_OBJECT_POOL_SIZE			( 150 )
/* See https://freertos.org/a00110.html#configSYSTEM_CALL_STACK_SIZE for details. */
#define configSYSTEM_CALL_STACK_SIZE					( 128 )

//-------------------------------------------//

/* Define the interrupt handlers required by FreeRTOS */
#define xPortPendSVHandler              PendSV_Handler
#define vPortSVCHandler                 SVC_Handler
#define xPortSysTickHandler             SysTick_Handler


#endif /* FREERTOS_CONFIG_H */
