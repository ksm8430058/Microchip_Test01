/*
 * TIMERCOUNT04.c
 *
 * Created: 2022-06-21 오후 5:11:52
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/interrupt.h>
#include <avr/io.h>

unsigned char FND_DATA_TBL[] ={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,0X79,0X71,0X08,0X80};
volatile unsigned char time_s = 0;
volatile unsigned char Time_STOP = 0;

unsigned char timer0Cnt = 0;

int main(void)
{
   DDRA = 0xFF;
   DDRE = 0x00;
   TCCR2 = 0x05;
   OCR2 = 184;
   TIMSK = 0x80;
   TIFR |=1 << OCF2;
   
   EICRB = 0x03;		// 0000 0011 4를 상승엣지에서 사용
   EIMSK =0x10;			// 인터럽트 4 허용
   EIFR = 0x10;			// 인터럽트 4 플러그 클리어
   sei();
    while (1) 
    {
		PORTA = FND_DATA_TBL[time_s];
    }
	return 0 ;
}
SIGNAL(TIMER2_COMP_vect)
{
	cli();		//인터럽트 금지
	OCR2 += 184;	//0.01초 후에 인터럽트 발생
	timer0Cnt++;
	if(timer0Cnt == 50)
	{
		
		if(Time_STOP == 0)
		{
			if(time_s >=16) time_s = 0;
			else time_s++;
		}
		timer0Cnt=0;
	}	
	sei();
}
SIGNAL(INT4_vect)
{
	
	cli();
	if(Time_STOP == 0) Time_STOP = 1;
	else Time_STOP = 0;
	sei();
}

