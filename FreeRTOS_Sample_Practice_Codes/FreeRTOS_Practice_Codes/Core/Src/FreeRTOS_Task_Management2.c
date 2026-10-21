/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

TIM_HandleTypeDef htim6;

#define STACK_SIZE 128

TaskHandle_t task1Handle;
TaskHandle_t task1Handle2;
TaskHandle_t task1Handle3;


void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
      /* Call tick handler */
    	xPortSysTickHandler();
    }
}

void monitorTask(void *para)
{
	uint8_t val = 0;
	bool Stat = false;
	TimeOut_t RefTimet;
	TickType_t RequiredTimet = 5000;

	vTaskSetTimeOutState(&RefTimet);
  while(1)
  {
	if(xTaskCheckForTimeOut(&RefTimet, &RequiredTimet) == pdTRUE)
	{
		// Timeout occured
		vTaskSetTimeOutState(&RefTimet);
		RequiredTimet = 5000;

		Stat = ! Stat;
		if(Stat)
		{
			vTaskSuspend(task1Handle2);
			vTaskSuspend(task1Handle3);
		}
		else
		{
			vTaskResume(task1Handle2);
			vTaskResume(task1Handle3);
		}
	}
  }
}

void Task2 (void* para)
{
	BaseType_t delaystate;
	
	TickType_t tickCount = xTaskGetTickCount();
	while(1)
	{
		delaystate = xTaskDelayUntil(&tickCount, pdMS_TO_TICKS(200));
		if(delaystate == pdTRUE)
		{
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
		}
	}
}

void Task3 (void* para)
{
	BaseType_t delaystate;
	
	TickType_t tickCount = xTaskGetTickCount();
	while(1)
	{
		delaystate = xTaskDelayUntil(&tickCount, pdMS_TO_TICKS(200));
		if(delaystate == pdTRUE)
		{
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
		}
		
	}
}

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_TIM6_Init();


	if(xTaskCreate(monitorTask,
			"SampleTask",
			STACK_SIZE,
			NULL,
			tskIDLE_PRIORITY + 4,
			&task1Handle) == pdFAIL)
	{
	// Task created
		while(1);
	}

	if(xTaskCreate(Task2,
				"Task2",
				STACK_SIZE,
				NULL,
				tskIDLE_PRIORITY + 2,
				&task1Handle2) == pdFAIL)
	{
		while(1);
	}

	if(xTaskCreate(Task3,
				"Task3",
				STACK_SIZE,
				NULL,
				tskIDLE_PRIORITY + 1,
				&task1Handle3) == pdFAIL)
	{
		while(1);
	}

	vTaskStartScheduler();
  
	//osKernelStart();
	while (1)
	{
	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
	}

}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : Switch_Pin */
  GPIO_InitStruct.Pin = Switch_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Switch_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC8 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

}

static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 30000;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1600 - 1;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */
  HAL_TIM_Base_Start_IT(&htim6);
  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


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
    		//GPIO_TogglePin(GPIOC, GPIO_PIN_8);
            //Delay_ms(10);
	while(1);
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
