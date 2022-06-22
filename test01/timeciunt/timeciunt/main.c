/*
 * timeciunt.c
 *
 * Created: 2022-06-21 오후 3:31:12
 * Author : PKNU
 */ 
#define F_CPU 7372800
#include <avr/interrupt.h>
#include <avr/io.h>

volatile unsigned char LED_Data =0x00;
unsigned char timer0Cnt =0;
SIGNAL(TIMERO_OVF_vect);
int main(void)
{
    DDRC = 0x0F;
	TCCR0 = 0x07;
	TCNT0 = 184;			//255에서 256으로 넘어갈때 오버플로우가 발생하니 결국은 266-((7372800/1024)/100)
	TIMSK = 0x01;
	TIFR |= 1 << TOV0;
	sei();	
    while (1) 
    {
		PORTC = LED_Data;
    }
}
SIGNAL(TIMER0_OVF_vect)
{
	cli();
	TCNT0 = 184;
	timer0Cnt++;
	if(timer0Cnt == 100)
	{
		LED_Data++;
		if(LED_Data>0x0f) LED_Data =0;
		timer0Cnt =0;
	}
	sei();
}

