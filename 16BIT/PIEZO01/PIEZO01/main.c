/*
 * PIEZO01.c
 *
 * Created: 2022-06-23 오후 1:42:58
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

unsigned int DoReMi[8] ={523,587,659,698,783,880,987,1046};
volatile unsigned char sound_flag = 1;

int main(void)
{	
    DDRE = 0x08;
	
	TCCR3A= 0x00;
	TCCR3B = 0x19;
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	EICRB = 0xFF;
	EIMSK = 0xF0;
	EIFR = 0xF0;
	sei();
    while (1) 
    {
		if(sound_flag)
		{
			_delay_ms(500);
			TCCR3A = 0x00;
			sound_flag =0;
		}
	}
}
SIGNAL(INT4_vect)
{
	
	cli();
	ICR3 = 7372800/DoReMi[0]/8;
	TCCR3A = 0x40;
	sound_flag = 1;
	sei();
}
SIGNAL(INT5_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[1]/8;
	TCCR3A = 0x40;
	sound_flag = 1;
	sei();
}
SIGNAL(INT6_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[2]/8;
	TCCR3A = 0x40;
	sound_flag = 1;
	sei();
}
SIGNAL(INT7_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[3]/8;
	TCCR3A = 0x40;
	sound_flag = 1;
	sei();
}
