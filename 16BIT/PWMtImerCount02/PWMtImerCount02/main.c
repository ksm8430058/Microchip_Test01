/*
 * PWMtImerCount02.c
 *
 * Created: 2022-06-22 오후 4:41:41
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/interrupt.h>
#include <avr/io.h>

volatile int Light = 0;
volatile unsigned char Light_flag =1;

int main(void)
{
    DDRB = 0x80;		// b 포트 출력 1000 0000, led0 = pb7
	DDRE = 0x00;		// E포트 입력
	
	// TCCR2 = 0x62;		// 0110 0010 , 2번을 제어레지스터로 사용
	TCCR2 = (1 << WGM20) | (1 << COM21) | (1 << CS21) ;
	//  PWM 모드 ,clear 상승 ,8 분주 
	
	TCNT2 = 0x00;		//타이머 2 카운트 초기화
	
	//EICRB = 0xFF;		// 1111 1111 
	EICRB = (1 << ISC40) | ( 1 << ISC41) | (1 << ISC50) | (1 << ISC51) | (1 << ISC60) | (1 << ISC61) | (1 << ISC70) | ( 1 << ISC71);
	// 인터럽트 4, 5, 6, 7을 상승엣지에서 인터럽트 발생시킴
	
	EIMSK = 0xF0;		// 1111 0000 -> 4, 5 ,6,7번 인터럽트 허용
	EIFR = 0xF0;		//인터럽트 4,5,6,7 플래그 클리어
	sei();				// 전체 인터럽트 허용
	
    while (1) 
    {
		if(Light_flag)			// 1일때 (1에서 시작)
		{
			OCR2 = Light;		// 출력비교 레지스터 2핀에 출력펄스 결정, light  값에 따라 밝기 제어
			Light_flag = 0;		// 0으로 하강(1->0)
		}		// 인터렙트 서비스 루틴에서 light_flag 가 1로세팅되어와서 메인문으로 다시돌아오면 0으로 변화
    }
}
SIGNAL(INT4_vect)				//4번 인터럽트 서비스 루틴(라이트 끄기)
{
	cli();						//전체인터럽트 금지
	Light = 0;					// 라이트 끄기
	Light_flag = 1 ;			//라이트 플래그 1 (0-> 1 상승)
	sei();						// 전체인터럽트 허용
}

SIGNAL(INT5_vect)			//5번인터럽트 서비스 루틴(라이트 밝기 감소 -51)
{
	cli();					// 전체인터럽트 금지
	Light -= 51 ;			// 라이트 밝기 감소
	if(Light<0) Light = 0;	//라이트의 값이 0보다 작은경우 라이트 끄기
	Light_flag = 1;			//라이트 플래그 1
	sei();					//전체 인터럽트 허용
}

SIGNAL(INT6_vect)			//6번 인터럽트 서비스 루틴(라이트 밝기 + 51 증가)
{
	cli();					//전체인터럽트 금지
	Light += 51;			
	if(Light >255) Light = 255;	//라이트의 밝기가 100%보다 크면 라이트는 100
	Light_flag = 1;				//
	sei();
}

SIGNAL(INT7_vect)			// 7번인터럽트 서비스 루틴(라이트 밝기 100)
{
	cli();
	Light =255;
	Light_flag = 1;
	sei();
}

