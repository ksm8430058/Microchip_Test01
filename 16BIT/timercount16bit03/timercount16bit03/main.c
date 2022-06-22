/*
 * timercount16bit03.c
 *
 * Created: 2022-06-22 오후 12:24:58
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/interrupt.h>
#include <avr/io.h>

volatile unsigned char time_s = 0;	//초를 세는 변수
unsigned char FND_DATA_TBL[] = {0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,
								0X79,0X71,0X08,0X80};			//세그먼트 표시글자


int main(void)
{
   DDRA = 0xFF ;		//출력포트 A , 1111 1111 -> 모두켜짐
   
   TCCR1A = 0x00;		// 1번 레지스터 사용 일반모드
   TCCR1B = (1 << CS10) | (1 << CS12);  // 1번 제어 레지스터 0x05 -> 0000 0101 -> 1024 
   
   OCR1A =	7200;				// 출력비교 인터럽트, 클럭주파수 주기 1초 7372800 / 1024;
   TIMSK = (1 << OCIE1A);		// 0001 0000 출력비교 인터럽트 값일치시 플레그 세트  
   TIFR =(1 << OCF1A);			// 0001 0000 타이머 인터럽트 플래그를 출력비교(OCR1A와 비교 같으면 1로 세트후 출력)
   sei();						//전체인터럽트 
    while (1) 
    {
		 PORTA = FND_DATA_TBL[time_s];		//초를 세는 변수를 넣어서 세그먼트의 글자를 출력
    }
	return 0 ;
}
SIGNAL(TIMER1_COMPA_vect)			//타이머카운터  1 
{
	cli();			//인터럭트 금지
	
	OCR1A += 7200;		// 1초후에 인터럽트 발생
	if(time_s >= 17)time_s =0; //변수는 17까지 16비트
	else time_s++;
	sei();			//0으로 초기화
	
}
