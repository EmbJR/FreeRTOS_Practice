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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* Definitions for TaskH */
osThreadId_t TaskHHandle;
const osThreadAttr_t TaskH_attributes = {
  .name = "TaskH",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh7,
};
/* Definitions for TaskL */
osThreadId_t TaskLHandle;
const osThreadAttr_t TaskL_attributes = {
  .name = "TaskL",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TaskM */
osThreadId_t TaskMHandle;
const osThreadAttr_t TaskM_attributes = {
  .name = "TaskM",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow7,
};
/* Definitions for Mutex_1 */
osMutexId_t Mutex_1Handle;
const osMutexAttr_t Mutex_1_attributes = {
  .name = "Mutex_1"
};
/* Definitions for myEvent01 */
osEventFlagsId_t myEvent01Handle;
const osEventFlagsAttr_t myEvent01_attributes = {
  .name = "myEvent01"
};
/* USER CODE BEGIN PV */

osSemaphoreId_t semaphore1;
uint8_t trigger = 0;
const osSemaphoreAttr_t sm_attr = {
		.name = "mySemaphore1"
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void TaskH_Func(void *argument);
void TaskL_Func(void *argument);
void TaskM_Func(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		trigger = 1;
		//osSemaphoreRelease(Mutex_1Handle);
		portYIELD_FROM_ISR(pdTRUE);
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of Mutex_1 */
  Mutex_1Handle = osMutexNew(&Mutex_1_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  semaphore1 = osSemaphoreNew(1, 1, &sm_attr);
  osThreadId_t getID = osMutexGetOwner(Mutex_1Handle);
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of TaskH */
  TaskHHandle = osThreadNew(TaskH_Func, NULL, &TaskH_attributes);

  /* creation of TaskL */
  TaskLHandle = osThreadNew(TaskL_Func, NULL, &TaskL_attributes);

  /* creation of TaskM */
  TaskMHandle = osThreadNew(TaskM_Func, NULL, &TaskM_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  osPriority_t pTaskH = osThreadGetPriority(TaskHHandle);
  osPriority_t pTaskL = osThreadGetPriority(TaskLHandle);
  osPriority_t pTaskM = osThreadGetPriority(TaskMHandle);
  /* USER CODE END RTOS_THREADS */

  /* creation of myEvent01 */
  myEvent01Handle = osEventFlagsNew(&myEvent01_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  HAL_GPIO_WritePin(GPIOC, LED1_Pin|LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin LED2_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_TaskH_Func */
/**
  * @brief  Function implementing the TaskH thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TaskH_Func */
void TaskH_Func(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
	osDelay(200);
  for(;;)
  {
	  osStatus_t stat = osMutexAcquire(Mutex_1Handle, portMAX_DELAY);
	  ////osStatus_t stat = osSemaphoreAcquire(semaphore1, portMAX_DELAY);
	  if(stat == osOK)
	  {
		  HAL_GPIO_TogglePin(GPIOC, LED2_Pin);
		  for(volatile uint32_t i = 0; i < 500000; i++);
		  osMutexRelease(Mutex_1Handle);
		  ////osSemaphoreRelease(semaphore1);
	  }
	  osDelay(100);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_TaskL_Func */
/**
* @brief Function implementing the TaskL thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskL_Func */
void TaskL_Func(void *argument)
{
  /* USER CODE BEGIN TaskL_Func */
  /* Infinite loop */
	int i = 0;
  for(;;)
  {
	  osStatus_t stat = osMutexAcquire(Mutex_1Handle, portMAX_DELAY);
	  ////osStatus_t stat = osSemaphoreAcquire(semaphore1, portMAX_DELAY);
	  if(stat == osOK)
	  {
		  for(volatile uint32_t i = 0; i < 1500000; i++);
		  if(trigger == 1)
		  {
			  trigger = 0;
			  for(i = 0; i < 500000; i++)
			  {
				  osPriority_t pTaskH = osThreadGetPriority(TaskHHandle);
				  osPriority_t pTaskL = osThreadGetPriority(TaskLHandle);
				  osPriority_t pTaskM = osThreadGetPriority(TaskMHandle);
			  }
		  }
		  osMutexRelease(Mutex_1Handle);
		  ////osSemaphoreRelease(semaphore1);
		  osDelay(100);
	  }

  }
  /* USER CODE END TaskL_Func */
}

/* USER CODE BEGIN Header_TaskM_Func */
/**
* @brief Function implementing the TaskM thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskM_Func */
void TaskM_Func(void *argument)
{
  /* USER CODE BEGIN TaskM_Func */
  /* Infinite loop */
	osDelay(5000);
  for(;;)
  {
	  for(volatile uint32_t i = 0; i < 50000; i++);
  }
  /* USER CODE END TaskM_Func */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
