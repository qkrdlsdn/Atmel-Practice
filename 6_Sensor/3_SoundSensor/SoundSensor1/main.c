#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0x00;          // PD0 = Sound Sensor
	PORTD = 0xff;
	DDRA = 0xff;            // PB = LED
	DDRC = 0x00;
	
	unsigned char count = 0x00;
	
	while(1)
	{	
		if((PINC & 0x01) == 0x00)
		{
			count = 0x00;
		}
		else if(!(PIND & 0x01))
		{
			while(!(PIND & 0x01));
			
			count += 0x01;
			if(count > 0x0f)
				count = 0x0f;
		}
		
		PORTA = count;
		_delay_ms(100);
	}
}