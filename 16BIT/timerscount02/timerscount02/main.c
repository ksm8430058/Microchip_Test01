/*
 * timerscount02.c
 *
 * Created: 2022-06-22 오전 11:38:33
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/interrupt.h>
#include <avr/io.h>

volatile unsigned char LED_Data = 0x00;

int main(void)
{
    DDRC = 0x0F;			//출력
	
	TCCR3A = 0x00;		// 3번 레지스터 제어
	TCCR3B = (1 << CS32) | (1 << CS30);	// 0000 0101 프리스케일러 분주 1024
	TCNT3 =	58336;			// 카운터 레지스터 3번  <1초> 시작위치 지정
	ETIMSK = (1 << TOIE1 ); //마스크 레지스턴트 오버플로우 T0IE1 => 0000 0100 -> 0x04
	ETIFR = (1 << TOV3);    // 타이머 플래그 래지스턴트 타임 오버플로우 플래그가 1로 세트 // 0000 0100 
	sei();					//인터럭트 동작
	
     while (1) 
    {
		PORTC = LED_Data;
    }
	return 0 ;
}
SIGNAL(TIMER3_OVF_vect)		//인터럭트(타이머3에 오버플로우 )
{
	cli();		//인터럭트 금지
	TCNT3 = 58336;		//58336+1024 = >65536 1초에 한번씩 인터럽트
	LED_Data ++;
	
	if(LED_Data >0x0f) LED_Data = 0; //led데이터의 값이 0000 1111-> 15 이상인경우 led데이터 0으로 초기화 16비트라서
	sei(); //인터럭트 시작
}

