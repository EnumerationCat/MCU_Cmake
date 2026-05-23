#ifndef __MYCAN_H
#define __MYCAN_H
#include "stdint.h"
#include "stm32f1xx_hal.h"
void MyCAN_Init(void);
HAL_StatusTypeDef MyCAN_Transmit(uint32_t ID, uint8_t Length, uint8_t *Data);
uint8_t MyCAN_ReceiveFlag(void);
void MyCAN_Receive(uint32_t *ID, uint8_t *Length, uint8_t *Data);

#endif
