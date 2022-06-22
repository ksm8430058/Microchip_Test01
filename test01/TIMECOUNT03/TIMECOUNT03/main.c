/*
 * TIMECOUNT03.c
 *
 * Created: 2022-06-21 오후 4:20:27
 * Author : PKNU
 */ 
#define  F_CPU 7372800UL
#include <avr/interrupt.h>
#include <avr/io.h>

//7세그먼트에 입력할 글자데이터 저장
unsigned char FND_DATA_TBL[] ={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,0X79,0X71,0X08,0X80};

volatile unsigned char time_s = 0;	//초를세는 변수
unsigned char timer0Cnt = 0;

int main(void)
{
	DDRA =0xFF;		//A출력
	
	TCCR0 = 0x07;
	OCR0 = 72;
	TIMSK = 0x02;
	TIFR |= 1 <<OCR0;		//출력비교 인터럽트 활성화
	sei();
    while (1) 
    {
		PORTA = FND_DATA_TBL[time_s];		//a에 table 값을 출력
    }
	return 0;
}
SIGNAL(TIMER0_COMP_vect)
{
	cli();
	OCR0 += 72;
	timer0Cnt++;
	
	if(timer0Cnt == 100)
	{
		if(time_s >= 16) time_s = 0; //16까지만 증가시키고 16되면 0
		else time_s++;
		timer0Cnt = 0;
	}
	sei();
}

