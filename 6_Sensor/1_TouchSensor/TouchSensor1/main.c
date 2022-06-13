#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>

uint8_t fnd[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x02, 0xf8, 0x80, 0x10};

void printFnd(int number)
{
	int num[4];
	
	num[0] = number%10;
	num[1] = ((number%100)-(number%10)) / 10;
	num[2] = ((number%1000)-(number%100)) / 100;
	num[3] = (number-(number%1000)) / 1000;
	
	PORTB=fnd[num[0]];
	PORTE=0x08; //일의 자리
	_delay_ms(3);
	PORTB=fnd[num[1]];
	PORTE=0x04; //십의 자리
	_delay_ms(3);
	PORTB=fnd[num[2]];
	PORTE=0x02; //백의 자리
	_delay_ms(3);
	PORTB=fnd[num[3]];
	PORTE=0x01; //천의 자리
	_delay_ms(3);
}

int main(void)
{
	DDRA = 0x00;
	DDRB = 0xff;
	DDRE = 0x0f;
	
	int count = 0;
	
    while (1) 
    {
		if ((PINA & 0x02) == 0x00)
		{
			while((PINA & 0x02) == 0x00)
				printFnd(count);
			
			count = 0;
		}
		
		if ((PINA | 0xfe) == 0xff)
		{
			while((PINA & 0x01) == 0x00)
			printFnd(count);
			
			count++;
		}
		
		printFnd(count);
    }
}