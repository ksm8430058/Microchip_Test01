/*
 * timercount04.c
 *
 * Created: 2022-06-22 오후 1:56:52
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/interrupt.h>
#include <avr/io.h>

unsigned char FND_DATA_TBL[] = {0x30,0x06,0x5 ,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X67,0X77,0X7C,
								0X39,0X5E,0X79,0X71,0X08,0X80};			//7세그먼트 글자출력 데이터 배열저장

volatile unsigned char time_s = 0;		//초를세는 변수
volatile unsigned char FND_flag =0;		//7세그먼트
volatile unsigned char edge_flag =0;	

int main(void)
{
	DDRA = 0xFF;	//포트 a 출력 , 1111 1111
	DDRE = 0x00;	//e 포트 입력
	
	TCCR3A = 0x00;	//3번 레지스터 사용 , 일반모드
	TCCR3B = (1 << ICES3) |(1 << CS32) | (1 << CS30); //0x45; // 0100 0101 , 1024분주사용 , 입력캡쳐플래그 인터럽트 발생
	ETIMSK =(1 << TICIE3);  // 0x20; // 0010 0000
	ETIFR = (1 << ICF3);	// 인풋인터럽트 플래스 발생 
	sei();					//인터럽트 전체시작
	PORTA = FND_DATA_TBL[0]; //포트에 7세그먼트 데이터 0으로 값 출력
    while (1) 
    {
		if(FND_flag)
		{
			if(time_s > 15) time_s = 15;		//만약 초를세는 변수가 15 이상인경우
			PORTA = FND_DATA_TBL[time_s];		// 포트 a에 테이블 값 출력
			FND_flag = 0;					
		}
    }
	return 0 ;
}
SIGNAL(TIMER3_CAPT_vect)
{
	cli();									//인터럽트 금지	
	unsigned int count_check;				// 스위치가 눌릴 시간 측정을 위해 상승->하강까지의 시간을 계산
	
	if(edge_flag == 0)						// 스위치를 누르면 (0 -> 1) 상승
	{
		TCCR3B = (1 << CS32) | (1 << CS30);//0x05;	// 0000 0101
		TCNT3 =0;							// 비교출력인터럽트
		ICR3 =0;							//입력 레지스터 0으로 초기화
		edge_flag = 1;						// 스위치 값 변경 1로
	}
	else									//스위치를 떼면 (1 ->0 )하강
	{
		TCCR3B = (1 << ICES3) |(1 << CS32) | (1 << CS30);	  // 0100 0101 , 1024분주사용 , 입력캡쳐플래그 인터럽트 발생
		count_check = ICR3 ;				// 변수에 입력레지스터 대입
		time_s = count_check/720;			// 0.1초단위로 변경 ,7372800 /1024 Hz 1초 7200
		FND_flag = 1;						// 7세그먼트로 측정시간을 출력 , 0~1.5초까지 측정가능
		edge_flag = 0;						//스위치 값 변경 (0 -> 1) 
	}
	sei();					//전체 인터럽트
}

