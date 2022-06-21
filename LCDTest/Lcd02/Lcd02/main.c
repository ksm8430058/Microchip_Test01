/*
 * Lcd02.c
 *
 * Created: 2022-06-20 오후 4:15:36
 * Author : PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Lcd.h"

unsigned char exchange =0;
SIGNAL(INT4_vect)
{
	cli();
	if(exchange == 0)
	{
		exchange =1;  //상승
    }
	if(exchange != 0)
	{
		exchange = 0;
	}
	sei();
}
int main(void)
{
	unsigned int i, j;
	unsigned char str1 = " Stop!";
	unsigned char str2 = "sorry";
	char num[20];
	
	
	DDRA = 0xFF;
	DDRG = 0x0F;
	DDRD = 0x00;
	EICRB = 0x03; // 상승
	EIMSK = 0x10;
	EIFR = 0x10;
	
	Lcd_Init();
	Lcd_Clear();
    sei();
    while (1) 
    {
		for (i =1 ; i<10 ; i++)
		{
			for(j=1 ; j<10 ; j++)
			{
				if(exchange)
				{
					Lcd_Clear();
					Lcd_Pos(0,0);
					Lcd_STR(str1);
					Lcd_Pos(1,0);
					Lcd_STR(str2);
				}
				else
				{
					while(!exchange)
					{
						Lcd_Clear();
						Lcd_Pos(0,0);
						sprintf(num,"%d * %d =%d",i,j-1,(i*(j-1)));
						Lcd_STR(num);
						Lcd_Pos(1,0);
						sprintf(num,"%d * %d =%d",i,j,i*j);
						Lcd_STR(num);
						_delay_ms(500);
					}
				}
			}
		}
		
    return 0;
   }
}

