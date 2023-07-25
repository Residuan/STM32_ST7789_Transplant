#include "SPI.h"

void SPI_Config(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_Init(SPI1, &SPI_InitStructure);
    SPI_Cmd(SPI1, ENABLE);

    SPI_SS_Stop();
}

uint8_t SPI_SendData(uint8_t Data)
{
    while ( SPI_I2S_GetFlagStatus(MySPIx, SPI_I2S_FLAG_TXE) != SET);

    SPI_I2S_SendData(MySPIx, Data);

    while (SPI_I2S_GetFlagStatus(MySPIx, SPI_I2S_FLAG_RXNE) != SET );
    
    return SPI_I2S_ReceiveData(MySPIx);
}


void SPI_RST_Set(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_0);
}

void SPI_RST_Reset(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_0);
}

void SPI_DC_Cmd(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_2);
}

void SPI_DC_Data(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_2);
}

void SPI_SS_Stop(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_1);
}

void SPI_SS_Start(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_1);
}

void LCD_BLK_Start(void)
{
		GPIO_SetBits(GPIOF, GPIO_Pin_3);
}

void LCD_BLK_Stop(void)
{
		GPIO_ResetBits(GPIOF, GPIO_Pin_3);
}


