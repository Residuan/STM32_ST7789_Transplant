#include "stm32f10x.h"
#include "USART.h"
#include "SPI.h"
#include "st7789.h"

int main(void)
{
	USART_Config();
	SPI_Config();
	ST7789_Init();
	printf("开机初始化完成\r\n");

	LCD_BLK_Start();

	while (1)
	{
//		ST7789_Test();
	}
}
