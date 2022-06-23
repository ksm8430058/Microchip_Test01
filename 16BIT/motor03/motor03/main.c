/*
 * motor03.c
 *
 * Created: 2022-06-23 오후 3:30:32
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <util/delay.h>
#include <avr/io.h>

// 시계방향
//1상 10,20,40,80
//2상 30,60,c0,90
unsigned char Step[8] = {0x90,0x80,0xC0,0x40,0x60,0x20,0x30,0x10};			//1상 2상 제어신호
	
int main(void)
{
	unsigned char i, t =0;
	
	DDRD = 0xF0;   
    while (1) 
    {
		// 명령당 3.75도 회전, 90도 회전하려면 총 24개의 명령이 필요
		for ( i = 0; i < 24 ; i++ )
		{
			PORTD = Step[t];					// 한 스텝 실행
			t++; 								// 다음 스텝 실행을 위해 t 증가
			if(t > 7) t = 0;					// 8 스텝을 초과하지 않도록 초기화
			_delay_ms(5);
		}
		_delay_ms(1000);
    }
}

