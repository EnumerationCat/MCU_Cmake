
#include "timer.h"



/* 定时器句柄全局定义 */
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim7;

/**
  * @brief  TIM2 基本定时中断初始化
  * @param  无
  * @retval 无
  */
void MX_TIM2_Init(void)
{
  /* 1. 开启TIM2时钟 */
  __HAL_RCC_TIM2_CLK_ENABLE();

  /* 2. 定时器基础配置 */
  htim2.Instance = TIM2;                  // 选择定时器2
  htim2.Init.Prescaler = 168-1;              // 预分频器：168MHz / (168) = 1MHz
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP; // 向上计数模式
  htim2.Init.Period = 10-1;                // 自动重装载值：1MHz / (10) = 10us
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // 时钟分频
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; // 自动重装载失能

  /* 3. 初始化定时器 */
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler(); // 初始化失败处理
  }

  /* 4. 配置定时器中断优先级 */
  HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0); // 抢占优先级5，子优先级0
  HAL_NVIC_EnableIRQ(TIM2_IRQn);         // 使能TIM2中断

}


/**
  * @brief  TIM2 基本定时中断初始化
  * @param  无
  * @retval 无
  */
void MX_TIM7_Init(void)
{
  /* 1. 开启TIM7时钟 */
  __HAL_RCC_TIM7_CLK_ENABLE();

  /* 2. 定时器基础配置 */
  htim7.Instance = TIM7;                  // 选择定时器7
  htim7.Init.Prescaler = 1680-1;              // 预分频器：168MHz / (1680) = 100kHz
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP; // 向上计数模式
  htim7.Init.Period = 100-1;                // 自动重装载值：100kHz / (100) = 1kHz
  htim7.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // 时钟分频
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; // 自动重装载失能

  /* 3. 初始化定时器 */
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler(); // 初始化失败处理
  }

  /* 4. 配置定时器中断优先级 */
  HAL_NVIC_SetPriority(TIM7_IRQn, 5, 0); // 抢占优先级5，子优先级0
  HAL_NVIC_EnableIRQ(TIM7_IRQn);         // 使能TIM7中断

}


/**
  * @brief  定时器底层MSP初始化（时钟、引脚等硬件初始化）
  * @param  tim_handle: 定时器句柄
  * @retval 无
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{
  if(tim_baseHandle->Instance==TIM2)
  {
    // 时钟已在MX_TIM2_Init中开启，此处无需重复配置
  }
  if(tim_baseHandle->Instance==TIM7)
  {
    // TIM7的初始化代码（如果需要使用TIM7）
  }
}



void MyTIM_Init(void)
{
  MX_TIM2_Init();
  MX_TIM7_Init();
	HAL_TIM_Base_Start_IT(&htim7);
	HAL_TIM_Base_Start_IT(&htim2);
}

/**
  * @brief  TIM2中断服务函数
  * @param  无
  * @retval 无
  */
void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2); // HAL库通用中断处理
}


/**
  * @brief  TIM7中断服务函数
  * @param  无
  * @retval 无
  */
void TIM7_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim7); // HAL库通用中断处理
}



#include "key.h"
volatile unsigned long ulHighFrequencyTimerTicks;
// 定时器更新中断回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  //定时器7每1ms触发一次
  if(htim->Instance == TIM7) 
  {


	  Key_Tick(); // 调用按键处理函数
		
  }

  if(htim->Instance == TIM2)
  {
	  ulHighFrequencyTimerTicks++;

  }
  
}



