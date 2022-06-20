/*
 * interrupt03.c
 *
 * Created: 2022-06-20 오전 10:51:22
 * Author : PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Shift_flag =1;
SIGNAL(INT5_vect)
{
	cli();
	Shift_flag = 1;
	sei();	
}
SIGNAL(INT7_vect)
{
	cli();
	Shift_flag =2;
	sei();
}
int main(void)
{
	unsigned char LED_Data = 0x01;
	
	DDRC = 0xfF; //0000 1111
	DDRE = 0x00;
	
	EICRB = 0xC8;
	EIMSK = 0xA0;
	EIFR = 0xA0;
	sei();
	while(1)
	{
		PORTC = LED_Data;
		if(Shift_flag == 1)
		{
			if(LED_Data == 0x80)LED_Data =0x01;
			else LED_Data <<= 1;
		}
		else if(Shift_flag ==2)
		{
			if(LED_Data == 0x01) LED_Data == 0x80;
			else LED_Data >>= 1;
		}
		_delay_ms(300);
		
	}	
}