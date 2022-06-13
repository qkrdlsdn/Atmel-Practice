#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
//#include "LCD16x2_4bit.h"
#include "../../../../../2021_semester_1/Atmel_Studio/avr/gpio/project_header/semester1_header.h"
#define DHT11_PIN 2
uint8_t c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

void Request()				// ATMega128로 스타트 펄스 전달 & 응답 과정
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);	// PD4 LOW
	_delay_ms(20);
	PORTD |= (1<<DHT11_PIN);	// PD4 HIGH
}
void Response()				// 온습도 센서로부터 응답
{
	DDRD &= ~(1<<DHT11_PIN); // PD4 LOW
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN))==0);
	while(PIND & (1<<DHT11_PIN));
}

uint8_t Receive_data()
{
	for (int q=0; q<8; q++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0); //비트가 0인지 1인지 체크
		_delay_us(30);
		if(PIND & (1<<DHT11_PIN)) //HIGH가 30ms보다 크면
		c = (c<<1)|(0x01);	 //HIGH 상태
		else
		c = (c<<1); //LOW 상태
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}

int main(void)
{
	DDRB = 0xff;
	LCD_PORT = &PORTB;
	
	char data[5];
	LCD_INIT();
	MOVE(1,1);		 // LCD 표시 위치
	STRING("Humidity =", sizeof("Humidity =")-1);
	MOVE(0,1);
	STRING("Temp = ", sizeof("Temp = ")-1);
	
	while(1)
	{
		Request();		 //시작 펄스 신호 보냄
		Response();		 //센서로부터 응답 받음
		I_RH=Receive_data();	 //습도의 정수 부분
		D_RH=Receive_data();	 //습도의 실수 부분
		I_Temp=Receive_data();	 //온도의 정수 부분
		D_Temp=Receive_data();	 //온도의 실수 부분
		CheckSum=Receive_data(); //모든 세그먼트의 체크섬
		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			CLEAR();
			MOVE(1,1);
			STRING("Error", sizeof("Error")-1);
		}
		else
		{
			itoa(I_RH,data,10);
			MOVE(1,12);
			STRING(data,sizeof(data)-3);
			STRING(".", 1);
			
			itoa(D_RH,data,10);
			STRING(data,sizeof(data)-4);
			STRING("%",1);
			
			MOVE(0,8);
			itoa(I_Temp,data,10);
			lcd_gotoxy(6,1);
			STRING(data,sizeof(data)-3);
			STRING(".",1);
			
			itoa(D_Temp,data,10);
			STRING(data,sizeof(data)-4);
			lcddata(0xDF);
			STRING("C ",1);
			
			_delay_ms(3000);
		}
	}
}