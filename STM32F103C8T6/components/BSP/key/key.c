#include "stm32f1xx_hal.h"

void Key_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;     
	GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Pin = GPIO_PIN_11 | GPIO_PIN_1;  
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure); 

}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 0)
	{
		HAL_Delay(20);
		while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 0);
		HAL_Delay(20);
		KeyNum = 1;
	}
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == 0)
	{
		HAL_Delay(20);

		while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == 0);
		HAL_Delay(20);
		KeyNum = 2;
	}
	
	return KeyNum;
}
