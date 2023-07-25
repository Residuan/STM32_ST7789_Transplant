#ifndef __SPI_H
#define __SPI_H

#define MySPIx    SPI1

#include "stm32f10x.h"

void SPI_Config(void);

void SPI_SS_Stop(void);
void SPI_SS_Start(void);
void SPI_DC_Cmd(void);
void SPI_DC_Data(void);
void SPI_RST_Set(void);
void SPI_RST_Reset(void);
uint8_t SPI_SendData(uint8_t Data);
void LCD_BLK_Start(void);
void LCD_BLK_Stop(void);



#endif



