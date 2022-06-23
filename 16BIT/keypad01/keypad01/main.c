/*
 * keypad01.c
 *
 * Created: 2022-06-23 오후 4:02:55
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <util/delay.h>
#include <avr/io.h>

unsigned char KeyScan();
int main(void)
{
	unsigned char key;
	// LOW 0(R0) PF3번으로 연결
   DDRA = 0xF8;			// A 포트 출력 0B 1111 1000 설정 -> 포트 4,5,6,7 입력(COW 세로), 상위 0,1,2,3 은 출력 (ROW, 가로)
   DDRC = 0xFF;
   
    while (1) 
    {
		KeyScan();
		if(key == '1') PORTC = 0x01;
    }
	return 0 ;
}
unsigned char KeyScan()
{
	PORTA = 0xF7 ;							// 0B 1111 0111 (입력 시그널 0)
	if(PINA == 0xF6)return '1'; 			// 1111 0110
	else if(PINA == 0xFD)return '2';		//1111  1101
	else if(PINA == 0xFB) return '3';		// 1111 1011
	_delay_ms(10);
	
	PORTA = 0xEF;					// 1110  FFFF	( 출력에 0이 돌아가며 뿌려줌 )
	if(PINA == 0xFE) return '4';			// 1111  1110
	else if(PINA == 0xFD)return '5'; 		// 1111  1101
	else if(PINA == 0xDB)return '6';		// 1111  1011
	_delay_ms(10);
	
	PORTA = 0xDF;					// 1101 FFFF
	if(PINA == 0xFE)return '7';				// 1111 1110
	else if(PINA == 0xFD)return '8'; 		// 1111  1101
	else if(PINA == 0xDB)return '9';		// 1111  1011
	_delay_ms(10);
	
	PORTA = 0xBF;					// 1011 FFFF
	if(PINA == 0xFE)return '*';				// 1111 1110
	else if(PINA == 0xFD)return '0'; 		// 1111  1101
	else if(PINA == 0xDB)return '#';		// 1111  1011
	_delay_ms(10);
	
}
