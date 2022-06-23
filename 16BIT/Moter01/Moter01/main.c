/*
 * Moter01.c
 *
 * Created: 2022-06-23 오후 2:42:14
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <util/delay.h>
#include <avr/io.h>


int main(void)
{
   DDRD = 0xF0;			// 출력포트 1111 0000 ,4,5,6,7 사용
    while (1) 
    {
		PORTD = 0x10;
		_delay_ms(8);				//1 STEP
					
		PORTD = 0x20;
		_delay_ms(8);				//2 STEP
		
		PORTD = 0x40;
		_delay_ms(8);				//3STEP
		
		PORTD = 0x80;
		_delay_ms(8);				//4 STEP
		
    }
}

