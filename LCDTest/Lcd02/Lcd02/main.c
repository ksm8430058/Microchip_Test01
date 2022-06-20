/*
 * Lcd02.c
 *
 * Created: 2022-06-20 오후 4:15:36
 * Author : PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"


int main(void)
{
	unsigned int i, j;
	char num[20];
	
	
	DDRA = 0xFF;
	DDRG = 0x0F;
	
	Lcd_Init();
	Lcd_Clear();
   
    while (1) 
    {
		for (i =1 ; i<10 ; i++)
		{
			for(j=1 ; j<10 ; j++)
			{
				Lcd_Pos(0,0);
				sprintf(num,"%d * %d =%d",i,j,i*j);
				Lcd_STR(num);
				_delay_ms(500);
			}
		}
    return 0;
   }
}

