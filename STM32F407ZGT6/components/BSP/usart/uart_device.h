#ifndef _UART_DEVICE_H
#define _UART_DEVICE_H


#ifdef __cplusplus
extern "C" {
#endif
    /*****************C*****************/
#include "main.h"

#define LOG_INFO(fmt, ...)  printf("%s:%s:%d: " fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)


void MX_USART1_UART_Init(void);
void MX_DMA_Init(void);

struct UART_Device {
    char *name;
    int (*Init)(struct UART_Device *pDev, int baud, int datas, char parity, int stop);
    int (*Send)(struct UART_Device *pDev, uint8_t *datas, int len, int timeout_ms);
    int (*Recv)(struct UART_Device *pDev, uint8_t *data, int timeout_ms);
    void *priv_data;
};

typedef struct UART_Device *PUART_Device;

struct UART_Device *GetUARTDevice(char *name);



#ifdef __cplusplus
}
/**********************C++*************************/

#endif

#endif 
