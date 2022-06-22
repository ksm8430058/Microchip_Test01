/*
 * TIMERCOUNT.c
 *
 * Created: 2022-06-22 오전 10:16:10
 * Author : PKNU
 */ 
#define F_CPU 7372800UL // -> 256번 클럭을 하면 1클럭 
#include <avr/interrupt.h>
#include <avr/io.h>

volatile unsigned char LED_Data = 0x00;
unsigned char timer1Cnt = 0; // 1초 7372800 / 1024 = 7200 -> 8비트로하면 너무커 7200 = 1초 72 = 0.01초 timercnt = 0.01 x 100 = 1초

int main(void)
{
	DDRC = 0x0f;
	
	TCCR1A = 0x00;				    // 0000 0000 동작모드 0 
	TCCR1B = (1 << CS12 );			//프리스케일러 1 설정 3b는 3번 프리스케일러	  
	TCNT1 = 36736;					//레지스타 1 번사용 65535 -> 0 256 -72 = 184 // 65536 - 28800(1초) = 
	TIMSK = (1 << TOIE1);			// 0000 0010 // 0000 0100->toie0  오버플로우 인터럽트 -> T0TIE1 ->0000 0010 0X04 0000 0100 TOIE = 1
	TIFR = (1 << TOV1);				// 플래그 레지스터에 비트 2사용  타임오버플래그 1 
	
	sei();
    while (1) 
    {
		PORTC = LED_Data;
    }
	return 0 ;
}
SIGNAL(TIMER1_OVF_vect)
{
	cli();
	timer1Cnt++; // 28800 ++; 
	
	if(timer1Cnt == 1)     // 1초 28800 
	{
		LED_Data++;
		if(LED_Data > 0x0F) LED_Data = 0;
		timer1Cnt =36736 ;
	}
	sei();
}

