#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

/* 全局定义CAN句柄（HAL库核心，必须定义） */
CAN_HandleTypeDef hcan1;


/**
  * @brief  CAN初始化函数（对外接口，与原函数名一致）
  * @retval None
  */
void MyCAN_Init(void)
{

	
    /* 使能时钟：GPIOA + CAN1 */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_CAN1_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStructure = {0};

    /* PA12 -> CAN_TX ：复用推挽输出 */
    GPIO_InitStructure.Pin   = GPIO_PIN_12;
    GPIO_InitStructure.Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* PA11 -> CAN_RX ：上拉输入 */
    GPIO_InitStructure.Pin   = GPIO_PIN_11;
    GPIO_InitStructure.Mode  = GPIO_MODE_INPUT; 
	GPIO_InitStructure.Pull  = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    hcan1.Instance = CAN1;  /* 绑定CAN外设 */

    /* ==================== CAN核心参数配置（与原标准库参数完全一致） ====================
     * APB1时钟 = 36MHz
     * 波特率 = 36M / Prescaler / (SyncSeg(1) + BS1 + BS2) = 36M/48/(1+2+3) = 125Kbps
     * ================================================================================= */
    hcan1.Init.Prescaler         = 48;                // 分频系数
    //hcan1.Init.Mode              = CAN_MODE_LOOPBACK;   // 回环模式
	hcan1.Init.Mode              = CAN_MODE_NORMAL;   // 正常模式
    hcan1.Init.SyncJumpWidth     = CAN_SJW_2TQ;       // 同步跳转宽度（原CAN_SJW_2tq）
    hcan1.Init.TimeSeg1          = CAN_BS1_2TQ;       // 时间段1（原CAN_BS1_2tq）
    hcan1.Init.TimeSeg2          = CAN_BS2_3TQ;       // 时间段2（原CAN_BS2_3tq）
    hcan1.Init.TimeTriggeredMode = DISABLE;           // 时间触发模式关闭
    hcan1.Init.AutoBusOff        = DISABLE;           // 自动离线关闭
    hcan1.Init.AutoWakeUp        = DISABLE;           // 自动唤醒关闭
    hcan1.Init.AutoRetransmission= DISABLE;           // 自动重传关闭（原NART=DISABLE）
    hcan1.Init.ReceiveFifoLocked = DISABLE;           // FIFO不锁定
    hcan1.Init.TransmitFifoPriority = DISABLE;       // 发送优先级关闭

    /* HAL库CAN初始化 */
    HAL_CAN_Init(&hcan1);


    /* ==================== CAN滤波器配置（与原逻辑一致：32位掩码，接收所有报文） ==================== */
    CAN_FilterTypeDef can_filter;
    can_filter.FilterBank           = 0;                      // 滤波器0
    can_filter.FilterMode           = CAN_FILTERMODE_IDMASK;  // 掩码模式
    can_filter.FilterScale          = CAN_FILTERSCALE_32BIT; // 32位宽
    can_filter.FilterIdHigh         = 0x0000;                 // ID高16位
    can_filter.FilterIdLow          = 0x0000;                 // ID低16位
    can_filter.FilterMaskIdHigh     = 0x0000;                 // 掩码高16位
    can_filter.FilterMaskIdLow      = 0x0000;                 // 掩码低16位
    can_filter.FilterFIFOAssignment = CAN_RX_FIFO0;           // 绑定FIFO0
    can_filter.FilterActivation     = ENABLE;                 // 使能滤波器
    can_filter.SlaveStartFilterBank = 0;                      // 单CAN无需配置

    HAL_CAN_ConfigFilter(&hcan1, &can_filter); // 配置滤波器


    /* 启动CAN（HAL库必须显式启动） */
    HAL_CAN_Start(&hcan1);
}



/**
  * @brief  CAN发送函数（与原函数名、参数、功能完全一致）
  * @param  ID: 标准帧ID
  * @param  Length: 数据长度(0-8)
  * @param  Data: 数据指针
  * @retval None
  */
HAL_StatusTypeDef MyCAN_Transmit(uint32_t ID, uint8_t Length, uint8_t *Data)
{
    CAN_TxHeaderTypeDef TxMessage;

    TxMessage.StdId = ID;   // 需发送消息的报文标准格式ID
    TxMessage.ExtId = ID;   // 需发送消息的报文扩展格式ID
    TxMessage.IDE = CAN_ID_STD; 
    // 需发送消息的报文类型，假如此处选择标准格式CAN_Id_Standard则ExtId无效；假如此处选择扩展格式CAN_Id_Extended则StdId无效
    TxMessage.RTR = CAN_RTR_DATA; // 设置需要发送的是数据帧
    TxMessage.DLC = Length; // 发送报文的长度

    uint32_t pTxMailbox;
    return HAL_CAN_AddTxMessage(&hcan1, &TxMessage, Data, &pTxMailbox);
}

/**
  * @brief  CAN接收就绪标志（与原函数功能一致）
  * @retval 1=有数据, 0=无数据
  */
uint8_t MyCAN_ReceiveFlag(void)
{
    // 由于前面配置过滤器时通过过滤器的报文进入FIFO0队列，且这个程序设置成了环回模式，自发自收。所以发
    // 文必会存入自身的FIFO0队列中
    uint32_t aaa = HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_FILTER_FIFO0);
    if (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_FILTER_FIFO0) > 0)
    {
        return 1;
    }
    return 0;
}

// 从FIFO0中读出数据
void MyCAN_Receive(uint32_t *ID, uint8_t *Length, uint8_t *Data)
{
    CAN_RxHeaderTypeDef RxMessage;
    HAL_CAN_GetRxMessage(&hcan1, CAN_FILTER_FIFO0, &RxMessage, Data); // 从FIFO0中读出数据
    if (RxMessage.IDE == CAN_ID_STD) // 判断读出的数据的ID类型
    {
        *ID = RxMessage.StdId;
    }
    else
    {
        *ID = RxMessage.ExtId;
    }

    if (RxMessage.RTR == CAN_RTR_DATA) // 判断读出的数据是数据帧还是遥控帧
    {
        // 数据帧处理
        *Length = RxMessage.DLC;
    }
    else
    {
        // 遥控帧处理
    }
}