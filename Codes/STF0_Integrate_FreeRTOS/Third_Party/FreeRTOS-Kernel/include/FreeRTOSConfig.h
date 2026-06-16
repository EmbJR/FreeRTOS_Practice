#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* Hardware specific settings */
#define configCPU_CLOCK_HZ              ( ( unsigned long ) 48000000 ) // Set to your system clock (e.g., 48MHz)
#define configTICK_RATE_HZ              ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES            ( 5 )
#define configMINIMAL_STACK_SIZE        ( ( unsigned short ) 128 )
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 4 * 1024 ) ) // Adjust based on your available RAM
#define configMAX_TASK_NAME_LEN         ( 10 )

/* RTOS behavioral settings */
#define configUSE_PREEMPTION            1
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0
#define configUSE_16_BIT_TICKS          0
#define configIDLE_SHOULD_YIELD         1
#define configUSE_MUTEXES               1
#define configUSE_RECURSIVE_MUTEXES     1
#define configUSE_COUNTING_SEMAPHORES   1

/* Memory Allocation */
#define configSUPPORT_STATIC_ALLOCATION     0
#define configSUPPORT_DYNAMIC_ALLOCATION    1

/* Hook definitions */
#define configCHECK_FOR_STACK_OVERFLOW  0

/* Cortex-M0 specific */
#define __NVIC_PRIO_BITS                2  // STM32F0 uses 2 bits for priority

/* Define the interrupt handlers required by FreeRTOS */
#define xPortPendSVHandler              PendSV_Handler
#define vPortSVCHandler                 SVC_Handler
#define xPortSysTickHandler             SysTick_Handler

#define configENABLE_MPU 0

#endif /* FREERTOS_CONFIG_H */
