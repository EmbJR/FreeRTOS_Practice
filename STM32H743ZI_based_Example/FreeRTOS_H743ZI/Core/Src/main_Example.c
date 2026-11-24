#include "main.h"

uint8_t data[200] = {};
volatile uint8_t Tasknum= 0;

#define STACK_SIZE 256

TaskHandle_t task1Handle;
TaskHandle_t task1Handle2;
TaskHandle_t task1Handle3;
TaskHandle_t task1Handle4;

static BaseType_t prvExampleTaskHook( void * pvParameter )
{
    /* Perform some action - this could be anything from logging a value,
       updating the task state, outputting a value, etc. */
	//HAL_UART_Transmit_IT(&huart3, (const uint8_t *)data, strlen((const char *)data));
	uint8_t ptrdata = *(uint8_t *)pvParameter;


    return 0;
}

void monitorTask(void *para)
{

	while(1)
	{

	}
}


void Task2 (void* para)
{
	uint8_t cnt = 0;
	while(1)
	{

	}
}

void Task3 (void* para)
{
	while(1)
	{
		vTaskDelay(1800);
	}
}

void Task4 (void* para)
{
	while(1)
	{
		vTaskDelay(1000);
	}
}

//void Task5 (void* para)
//{
//
//}


void FreeRTOSTestFun(uint8_t val)
{


	 if(xTaskCreate(monitorTask,
	  			"SampleTask",
	  			STACK_SIZE,
	  			(uint8_t *)&Tasknum,
	  			tskIDLE_PRIORITY + 3,
	  			&task1Handle) == pdFAIL)
	  	{
	  	// Task created
	  		while(1);
	  	}

	    Tasknum = 10;
	  	if(xTaskCreate(Task2,
	  				"Task2",
	  				STACK_SIZE,
					(uint8_t *)&Tasknum,
	  				tskIDLE_PRIORITY + 2,
	  				&task1Handle2) == pdFAIL)
	  	{
	  		while(1);
	  	}

	  	Tasknum = 20;
	  	if(xTaskCreate(Task3,
	  				"Task3",
	  				STACK_SIZE,
					(uint8_t *)&Tasknum,
	  				tskIDLE_PRIORITY + 1,
	  				&task1Handle3) == pdFAIL)
	  	{
	  		while(1);
	  	}

	  	if(xTaskCreate(Task4,
	  		  				"Task4",
	  		  				STACK_SIZE,
	  						(uint8_t *)&Tasknum,
	  		  				tskIDLE_PRIORITY + 1,
	  		  				&task1Handle4) == pdFAIL)
		{
			while(1);
		}

//	  	if(xTaskCreate(Task5,
//	  		  				"Task5",
//	  		  				STACK_SIZE,
//	  						(uint8_t *)&Tasknum,
//	  		  				tskIDLE_PRIORITY + 1,
//	  		  				&task1Handle5) == pdFAIL)
//		{
//			while(1);
//		}

	  	vTaskStartScheduler();
}

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    // Trigger a breakpoint or reset the system here
    while (1) {
		//GPIO_TogglePin(GPIOC, GPIO_PIN_9);
			//Delay_ms(1000);
	}
}

#if (configUSE_IDLE_HOOK == 1)
void vApplicationIdleHook(void) {
    // This runs whenever no other task is ready to run
    // Enter Sleep Mode
    //__WFI();
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}
#endif

void vApplicationMallocFailedHook(void)
{
    while(1)
    {
        /* Memory exhausted */
    	while(1);
    }
}
