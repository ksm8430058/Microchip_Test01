/*
 * timecount02.c
 *
 * Created: 2022-06-21 오후 4:06:56
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/interrupt.h>
#include <avr/io.h>

volatile unsigned char LED_Data =0x01;
unsigned char timer2Cnt = 0;
unsigned char Shift_Flag =0;

SIGNAL(TIMER2_OVF_vect);
int main(void)
{
   DDRC = 0x0F; //출력
   TCCR2 = 0x05;		//프리스케일러 1024
   
   TCNT0 = 184;			//0.01초마다 한번 인터럽트 발생
   TIMSK = 0x40;
   TIFR |=1 << TOV2 ;
   sei();
    while (1) 
    {
		PORTC = LED_Data;
    }
	return 0;
}
SIGNAL(TIMER2_OVF_vect)
{
	cli();
	TCNT2 = 184;
	timer2Cnt++;	//변수증가
	
	if(timer2Cnt == 50)			//0.5 초를 얻기위한 카운트
	{
		if(Shift_Flag ==0)
		{
			LED_Data <<= 1;		//led0~led3이동
			if(LED_Data == 0x08) Shift_Flag =1;	// led3으로 이동하면 우측으로 쉬프트하도록 설정
		}
		else
		{
			LED_Data >>=1 ;	//led3~led0으로 이동
			if(LED_Data == 0x01) Shift_Flag = 0;	//led0으로 이동하면 좌측으로 쉬프트
		}
		timer2Cnt = 0;
	}
	sei();
}

