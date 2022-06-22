/*
 * miniTest1.c
 *
 * Created: 2022-06-21 오전 11:51:25
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

unsigned char RX_data = 0;
unsigned char num[30];
void putch(unsigned char date)
{
	while((UCSR0A & 0x20) == 0);		// 전송대기
	UDR0 = date;						// 전송
	UCSR0A |= 0x20;						// 5번포트 사용
}
// void puts_USARO(char *str)
// {
// 	while(*str != 0)
// 	{
// 		puts_USARO(*str);
// 		str++;
// 	}		
// }
void putch_Str(char *str){
	
	unsigned char i = 0;
	while(str[i]!='\0')
	putch(str[i++]);
	
}

unsigned char getch()
{
	unsigned char data;					//송신대기
	while((UCSR0A & 0x80)==0);			//송신
	data=UDR0 ;							//데이터 저장
	UCSR0A |= 0x80;						//7번 포트 사용
	return data;
}
int main(void)
{
	unsigned char i =0;
    DDRA = 0xfe	;						//입력 0, 출력 1
	DDRD = 0xFF;						//출력
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;						// Rx, Tx enable
	UCSR0C = 0x06;						// 비동기 방식, No Parity bit, 1 Stop bit
	UBRR0H = 0x00;				
	UBRR0L = 3;							// 115200 bps
	
	
	while(1)	
	{
		RX_data = getch();				// getch로 입력받은 값을 변수저장

		int i = RX_data - 0x30; 
		//int	i =  atoi(*RX_data);
		
		for(int j =0;j<10;j++)
		{
 			sprintf(num,"%d * %d = %d\r\n",i,j,i*j);
			putch_Str(num);
		}
// 		num2();
// 		while(i < 10)
// 		{
// 			sprintf(num,"%d * %d = %d",i,i+1,);
// 		}
// 		i =0;
// 		
// 		
    }
}

