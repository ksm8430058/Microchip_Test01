/*
 * USRT04.c
 *
 * Created: 2022-06-21 오전 11:41:41
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TX_flag = 0;
volatile char TX_dara;

// 7-Segment에 표시할 글자의 입력 데이터를 저장
unsigned char FND_DATA_TBL[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,0X79,0X71,0X08,0X80};

void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);		// 전송준비가 될때까지 대기
	UDR0 = data;						// 데이터를 UDR0에 쓰면 전송된다
	UCSR0A |= 0x20;
}
unsigned char getch(void)
{
	unsigned char data;
	while((UCSR0A & 0x80)==0);			// 데이타를 받을때까지 대기
	data=UDR0;							// 수신된 데이터는 UDR0에 저장되어 있다.
	UCSR0A |= 0x80;
	return data;						 // 읽어온 문자를 반환한다.
}
int main(void)
{
	unsigned char RX_data = 0;
	DDRE = 0x0e;					 // Rx(입력 0), Tx(출력, 1)
	DDRA = 0xFF;					// 포트A 를 출력포트로 설정한다.
	UCSR0A = 0x00;
	UCSR0B = 0x18;					// Rx, Tx enable
	UCSR0C = 0x06;					// 비동기 방식, No Parity bit, 1 Stop bit
	UBRR0H = 0x00;
	UBRR0L = 3;					// 115200 bps
    
    while (1) 
    {
		RX_data = getch();			 //PC로 부터 입력 받은 데이터를 변수 RX_data에 저장
		if((RX_data >= 0x30) && (RX_data <= 0x39))
		{
			PORTA = FND_DATA_TBL[RX_data - 0x30];	// 포트A에 입력된	값의 FND Table 값을 출력한다.
			// 아스키코드 '0'은 0x30 임.
		}
	}
}

