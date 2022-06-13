#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define M0_LOW	(PORTA &= 0xFE)
#define M0_HIGH	(PORTA |= 0x01)
#define M1_LOW	(PORTA &= 0xFD)
#define M1_HIGH	(PORTA |= 0x02)
#define M2_HIGH	(PORTA |= 0x04)
#define M2_LOW	(PORTA &= 0xFB)

void Port_init(void)
{
	DDRA = 0xff;
}

void delay_time(long t)
{
	long i ;
	for(i = 0 ; i < t ; i ++ ) ;
}

void MotorGo( long Dist, long Speed )
{
	long i;
	for( i = 0 ; i < Dist; i++ ) {
		M0_LOW; M1_HIGH;
		M2_HIGH;
		delay_time(Speed);
		M2_LOW;
		delay_time(5);
		M2_LOW;
		delay_time(100-Speed);  
	}
}

void MotorSTOP()
{
	M0_HIGH; M1_HIGH;
}

void main(void)
{
	Port_init();
	while(1)
	{
		MotorGo(500,20);
		delay_time(30000);
		MotorGo(500,40);
		delay_time(30000);
		MotorGo(500,60);
		delay_time(30000);
		MotorGo(500,80);
		delay_time(30000);
		MotorSTOP();

		delay_time(30000);
	}
}
