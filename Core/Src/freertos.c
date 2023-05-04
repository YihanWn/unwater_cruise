/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId ControlTaskHandle;
osThreadId PressureTaskHandle;
osThreadId MessageTaskHandle;
osThreadId LedTaskHandle;
osThreadId ImuTaskHandle;
osThreadId SensorTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void ControlTask_Function(void const * argument);
void PressureTask_Function(void const * argument);
void MessageTask_Function(void const * argument);
void LedTask_Function(void const * argument);
void ImuTask_Function(void const * argument);
void SensorTask_Function(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
	Task_Queue_Semaphore_Timers_Create();
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of ControlTask */
  osThreadDef(ControlTask, ControlTask_Function, osPriorityRealtime, 0, 1024);
  ControlTaskHandle = osThreadCreate(osThread(ControlTask), NULL);

  /* definition and creation of PressureTask */
  osThreadDef(PressureTask, PressureTask_Function, osPriorityIdle, 0, 128);
  PressureTaskHandle = osThreadCreate(osThread(PressureTask), NULL);

  /* definition and creation of MessageTask */
  osThreadDef(MessageTask, MessageTask_Function, osPriorityHigh, 0, 1024);
  MessageTaskHandle = osThreadCreate(osThread(MessageTask), NULL);

  /* definition and creation of LedTask */
  osThreadDef(LedTask, LedTask_Function, osPriorityIdle, 0, 128);
  LedTaskHandle = osThreadCreate(osThread(LedTask), NULL);

  /* definition and creation of ImuTask */
  osThreadDef(ImuTask, ImuTask_Function, osPriorityHigh, 0, 1024);
  ImuTaskHandle = osThreadCreate(osThread(ImuTask), NULL);

  /* definition and creation of SensorTask */
  osThreadDef(SensorTask, SensorTask_Function, osPriorityHigh, 0, 512);
  SensorTaskHandle = osThreadCreate(osThread(SensorTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_ControlTask_Function */
/**
  * @brief  Function implementing the ControlTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_ControlTask_Function */
__weak void ControlTask_Function(void const * argument)
{
  /* USER CODE BEGIN ControlTask_Function */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END ControlTask_Function */
}

/* USER CODE BEGIN Header_PressureTask_Function */
/**
* @brief Function implementing the PressureTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_PressureTask_Function */
__weak void PressureTask_Function(void const * argument)
{
  /* USER CODE BEGIN PressureTask_Function */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END PressureTask_Function */
}

/* USER CODE BEGIN Header_MessageTask_Function */
/**
* @brief Function implementing the MessageTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MessageTask_Function */
__weak void MessageTask_Function(void const * argument)
{
  /* USER CODE BEGIN MessageTask_Function */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END MessageTask_Function */
}

/* USER CODE BEGIN Header_LedTask_Function */
/**
* @brief Function implementing the LedTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LedTask_Function */
__weak void LedTask_Function(void const * argument)
{
  /* USER CODE BEGIN LedTask_Function */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END LedTask_Function */
}

/* USER CODE BEGIN Header_ImuTask_Function */
/**
* @brief Function implementing the ImuTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ImuTask_Function */
__weak void ImuTask_Function(void const * argument)
{
  /* USER CODE BEGIN ImuTask_Function */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END ImuTask_Function */
}

/* USER CODE BEGIN Header_SensorTask_Function */
/**
* @brief Function implementing the SensorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SensorTask_Function */
__weak void SensorTask_Function(void const * argument)
{
  /* USER CODE BEGIN SensorTask_Function */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END SensorTask_Function */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
