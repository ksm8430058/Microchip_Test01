/*
 * CTCTIMERCOUNT01.c
 *
 * Created: 2022-06-22 오후 4:14:46
 * Author : PKNU
 */ 
/*CTC *비교일치 (한계값에 도달하면)*/
/* FAST 비교일치일때 한번 오버플로우일때 한번더 */
/*PCPW 상향과 하향카운트 비교일치 두번*/
#define F_CPU 7372800UL
#include <util/delay.h>
#include <avr/io.h>


int main(void)
{	//8비트 사용
	unsigned  char Light = 0;
	
	DDRB = 0x10;	//포트 b를 출력포트 설정 0001 0000
	
	//TCCR0 = 0x76;	//제어 레지스터 0 사용  0111 0110
	TCCR0 = (1 << WGM00 )| ( 1 << COM01) | (1 << COM00) | (1 << CS02) | (1<< CS01);
	//  노말모드 , 업 다운 카운트 PC PWM 모드 , 256 분주
	TCNT0 = 0x00;	// 타이머 카운트 초기화
	
    while (1) 
    {
		for(Light = 0 ; Light<255;Light++)
		{
			OCR0 = Light;	//출력비교 레지스터 0번 사용, 0번핀에 출력펄스 결
			_delay_ms(10);	//10MS 지연
		}
		for (Light = 255; 0<Light;Light--)
		{
			OCR0 = Light;
			_delay_ms(10);
		}
    }
}

