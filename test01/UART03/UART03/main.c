/*
 * UART03.c
 *
 * Created: 2022-06-21 오전 11:21:28
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>

void putct(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);			//전송대기
	UDR0 = data;							//데이터 전송
	UCSR0A |=0x20;							// UCSR0A 레지스터 중에서 5번째 비트(UDREn) 를 세트하여 UDRE0를 클리어 함. */ 0010 0000
}
unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80) == 0);				// 송신 대기
	data = UDR0;							// 송신된 데이터 저장
	UCSR0A |= 0x80;							// 7번째 비트 세트 
	return data;							//데이터 반환
}

int main(void)
{
    unsigned char text[] = 
			"\r\nWelcom! edgeiLAB\r\n USART 0 Test Program.\r\r";
	unsigned char echo[] = "ECHO >>";
	unsigned char i = 0;
	
	DDRE = 0xfe;			//E포트 사용, Rx(입력0), Tx(출력 1)

	UCSR0A = 0x00;
	UCSR0B = 0x18;		// Rx, Tx enable
	UCSR0C = 0x06;		// 비동기 방식, No Parity bit, 1 Stop bit
	UBRR0H = 0x00;
	UBRR0L = 3;		// 115200 bps
    while (text[i]!='\0')		//문자열 데이터가 '\0'인경우, 문자열의 끝 
    {
		putct(text[i++]);		//문자열 출력
    }
	i = 0;
	while(echo[i]!='\0')		//위와 동일
	{
		putct(echo[i++]);
	}
	while(1)
	{
		putct(getch());
	}						// getch()로 입력받은 문자를 다시 putch()로 문자열 출력
}

