#include "USART.h"

void USART_Config(void)
{
    USART_InitTypeDef USART_Structure;
    GPIO_InitTypeDef GPIO_Structure;
    NVIC_InitTypeDef NVIC_Structure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_Structure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Structure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_Structure);

    GPIO_Structure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Structure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_Structure);

    USART_Structure.USART_BaudRate = 115200;
    USART_Structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Structure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Structure.USART_Parity = USART_Parity_No;
    USART_Structure.USART_StopBits = USART_StopBits_1;
    USART_Structure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_Structure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_Structure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_Structure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Structure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_Structure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_Structure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
}

void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    USART_SendData(pUSARTx, ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Usart_SendString(USART_TypeDef *pUSARTx, char *str)
{
    unsigned int k = 0;
    do
    {
        Usart_SendByte(pUSARTx, *(str + k));
        k++;
    } while (*(str + k) != '\0');

    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void USART1_IRQHandler(void)
{
    uint8_t data;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(USART1);
        USART_SendData(USART1, data);
    }
    USART_ClearFlag(USART1, USART_IT_RXNE);
}

int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return (ch);
}

int fgetc(FILE *f)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return (int)USART_ReceiveData(USART1);
}
