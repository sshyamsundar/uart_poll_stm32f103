#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "lcd16x2.h"
#include <string.h>

#define size 3
int i=0;
char buf[size];
void Usart_Init();

void Usart_Init()
{
 USART_InitTypeDef USART_Struct;
 GPIO_InitTypeDef GPIO_Struct;

 RCC_APB1PeriphClockCmd (RCC_APB1Periph_USART2, ENABLE);
 USART_Struct.USART_BaudRate = 9600;
 USART_Struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//
 USART_Struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 USART_Struct.USART_Parity = USART_Parity_No;
 USART_Struct.USART_StopBits = USART_StopBits_1;
 USART_Struct.USART_WordLength = USART_WordLength_8b;//
 USART_Init(USART2, &USART_Struct);
 USART_Cmd(USART2, ENABLE);//
 
 RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);
 GPIO_Struct.GPIO_Pin = GPIO_Pin_2;
 GPIO_Struct.GPIO_Mode = GPIO_Mode_AF_PP;//
 GPIO_Struct.GPIO_Speed = GPIO_Speed_2MHz;
 GPIO_Init (GPIOA, &GPIO_Struct);
 
 GPIO_Struct.GPIO_Pin = GPIO_Pin_3;
 GPIO_Struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 GPIO_Struct.GPIO_Speed = GPIO_Speed_2MHz;
 GPIO_Init(GPIOA, &GPIO_Struct);
}

void Gpio_Init()
{
 GPIO_InitTypeDef GPIO_Struct;
 
 RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);
 GPIO_Struct.GPIO_Pin = GPIO_Pin_3;
 GPIO_Struct.GPIO_Speed = GPIO_Speed_2MHz;
 GPIO_Struct.GPIO_Mode = GPIO_Mode_Out_OD;
 GPIO_Init(GPIOA, &GPIO_Struct);
}

int main(void)
{
 lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
 Gpio_Init();
 Usart_Init();
 while(1)
 {
   char c = USART2_GetChar();
   
  if(c != '\n')
   {
  if (i < size -1)
	{
	  buf[i] = c;
	  i++;
    }
	else
	{
	  buf[i] = c;
	  i=0;
	}
  }
   else 
   {
	lcd16x2_clrscr();
	lcd16x2_puts(buf);
/*   if(strcmp(buf,"on",2) == 0)
	 {
	   GPIO_SetBits(GPIOA, GPIO_Pin_3);
	  }
	  else if(strcmp(buf,"off",3) == 0)
	  {
	    GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	  }
	  memset(&buf[0], 0, sizeof(buf));
    }*/
  }
 }
 }

 uint16_t USART_GetChar()
{
 while (!USART_GetFlagStatus(USART2, USART_FLAG_RXNE));
 return USART_ReceiveDATA(USART2);
}