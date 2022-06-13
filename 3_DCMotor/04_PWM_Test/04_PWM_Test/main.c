#define F_CPU	16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void Port_Init()
{
	//dc motor
	DDRB=0x60;
	TCCR1A=0x82;
	TCCR1B=0x1A;
	OCR1A=0;
	OCR1B=0;
	ICR1=100;
	//button
	DDRE = 0x00;
	//led
	DDRC = 0xff;
}

//volatile char speed=0;
void DC_Motor(int speed)
{
	if(speed< 0) speed= 0;
	if(speed>100) speed=100;
	OCR1A=speed;
}

int Btn_click(uint8_t index)
{
	if ((PINE&index) == 0x00)
	{
		return 1;
	}
	return 0;
}

int main(void)
{
	int speed = 0;
	Port_Init();
	
	while(1)
	{
		// up
		if(Btn_click(0x10))
		{
			while(Btn_click(0x10));
			
			if(speed == 0)	speed = 60;
			else	speed += 10;
		}
		//down
		if(Btn_click(0x20))
		{
			while(Btn_click(0x20));
			if(speed == 60) speed = 0;
			else	speed -= 10;
		}
		//stop
		if(Btn_click(0x40))
		{
			while(Btn_click(0x40));
			speed = 0;
		}
		
		if (speed > 100)	speed = 100;
		if (speed < 0)	speed = 0;
		
		if(speed == 0)	PORTC = 0xFE;
		if(speed == 60)	PORTC = 0xFD;
		if(speed == 70)	PORTC = 0xFB;
		if(speed == 80)	PORTC = 0xF7;
		if(speed == 90)	PORTC = 0xEF;
		if(speed == 100)	PORTC = 0xDF;
		
		DC_Motor(speed);
	}
}

