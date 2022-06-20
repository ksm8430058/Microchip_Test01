/*
 * Interript02.c
 *
 * Created: 2022-06-20 오전 10:40:05
 * Author : PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char count;
SIGNAL(INT0_vect)
{
	count++;	
}   //많은것을 담고 있으면안된다.
int main(void)
{
	DDRD = 0x00;
	DDRA = 0xff;
	EIMSK = 0x01;
	EICRA = (1 << ISC01) | (0 << ISC00);
   sei();
    while (1) 
    {
		if(count%2 != 0)
		{
			PORTA = 0x01;
		}
		else if(count % 2 == 0)
		{
			PORTA = 0x00;
		}
    }
	return 0;
}

