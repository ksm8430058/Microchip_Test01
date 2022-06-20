/*
 * interript04.c
 *
 * Created: 2022-06-20 오후 2:26:32
 * Author : PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char exchange = 0;
SIGNAL(INT4_vect)
{
	cli();
	if(exchange == 0)
	{
		exchange = 1;
	}
	else
	{
		exchange = 0;
	}
	sei();
}

int main(void)
{ 
	unsigned char LED_Data = 0x01;
	
	DDRC = 0xFF;   //포트 C를 출력포트
	DDRE = 0x00;	//포트 E를 입력포트
	
	EICRB = 0x03;  // 인터럽트 4번을 상승엣지에서 동작하도록 설정
	EIMSK = 0x10;  //인터럽트 4번 허용
	EIFR = 0x10;  // 인터럽트 4번 플래그 클리어
	sei();
    while (1) 
    {
		PORTC = LED_Data; 
		if(!exchange)
		{
			if(LED_Data == 0x80)LED_Data = 0x01;
			else 
			LED_Data <<= 1;
		}
		_delay_ms(500);
    }
}

