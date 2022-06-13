#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define M0_HIGH (PORTA |= 0x01)
#define M0_LOW	(PORTA &= 0xfe)
#define M1_HIGH (PORTA |= 0x02)
#define M1_LOW	(PORTA &= 0xfd)

void Port_init()
{
	DDRA = 0xff;
}

int main(void)
{
	Port_init();
	
	while (1) 
	{
		M0_HIGH; M1_HIGH;
		_delay_ms(1000);
		M0_LOW; M1_HIGH;
		_delay_ms(1000);
		M0_HIGH; M1_HIGH;
		_delay_ms(1000);
		M0_HIGH; M1_LOW;
		_delay_ms(1000);
	}
}

