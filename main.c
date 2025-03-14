#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
	DDRA = 0xFF;	// 포트 설정
	DDRG &= ~((1<<4) | (1<<3) | (1<<2));  // 버튼 입력
	DDRB |= (1<<DDRB4);  //  PWM 출력 설정
	TCCR0 = (1<<WGM00) | (1<<COM01) | (1<<WGM01) | (1<<CS02) | (1<<CS01);
	OCR0 = 0;  // 초기 PWM 듀티값 설정

	while (1)
	{
		if (!(PING & (1<<4)))  // 4번 버튼이 눌리면
		{
			PORTA = 0x3F;  // 숫자 0 표시
			OCR0 = 0;  // PWM 끄기
		}
		else if (!(PING & (1<<3)))  // 3번 버튼이 눌리면
		{
			PORTA = 0x06;  // 숫자 1 표시
			for (uint8_t i = 0; i < 128; i += 5)  // OCR0 5씩 127까지 증가
			{
				OCR0 = i;
				_delay_ms(10);
			}

		}
		else if (!(PING & (1<<2)))  // 2번 버튼이 눌리면
		{
			PORTA = 0x5B;  // 숫자 2 표시
			for (uint8_t i = 0; i < 255; i += 5)  // OCR0 최대치까지 증가
			{
				OCR0 = i;
				_delay_ms(10);
			}

		}

	}
}
