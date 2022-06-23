/*
 * motor02.c
 *
 * Created: 2022-06-23 오후 3:14:19
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <util/delay.h>
#include <avr/io.h>

// 2상 시계방향
int main(void)
{
    unsigned char i;
	
	DDRD = 0xF0;
	
    while (1) 
    {
		for(i = 0 ; i<12; i++)			//2상 48스텝
		{
			PORTD = 0x30;				// 1스텝
			_delay_ms(5);
			PORTD = 0x90;				// 2 스텝
			_delay_ms(5);
			PORTD = 0xC0;				// 3스텝
			_delay_ms(5);
			PORTD = 0x60;				// 4스텝
			_delay_ms(5);
		}
		_delay_ms(1000);
    }
}

