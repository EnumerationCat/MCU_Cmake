
#include "stm32f1xx_hal.h"

void LED_Init(void)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;     
    GPIO_InitStructure.Pin = GPIO_PIN_13;  
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;    
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure); 


	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

}

void LED1_ON(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

void LED1_OFF(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

void LED1_Turn(void)
{
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	}
}

