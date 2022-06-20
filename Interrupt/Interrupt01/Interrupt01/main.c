/*
 * Interrupt01.c
 *
 * Created: 2022-06-20 오전 9:55:29
 * Author : PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char count;
SIGNAL(INT0_vect)
{
	count++;
	PORTA = count;
}
int main(void)
{
	DDRD = 0x00;
	DDRA = 0xFF;
	EIMSK = 0x01;  //INTO 활성화
	//EIMSK = 1 << INTO;
	//EICRA = 0x03;   //0b 0000 0000
	EICRA = 1 << ISC01 | 1 << ISC00;  //0b 0000 0000
	//1을 좌측으로 1번 이동시켜라 | 1을 좌측으로 0번 이동시켜라
	sei();

    while (1) 
    {
    }
	return 0;
}

