#include <avr/io.h>
#define F_CPU 16000000UL
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)
#include <util/delay.h>
#include <avr/interrupt.h>

void uart_init(unsigned int baud)
{
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char)baud;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0) |			(1<<RXCIE0);
}

void uart_write(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

int main(void)
{
	unsigned short value;
	DDRF = 0x00;
	DDRA = 0xff;
	PORTA = 0x01;

	uart_init(BAUDRATE(9600));
	sei();

    while (1) 
    {	
		if ((PINF | 0xfe) == 0xff)
		{
			PORTA=0x00;
			uart_write('1');
			uart_write('\n');
			
			_delay_ms(200);
		}
		else
		{
			PORTA=0x01;
		}
    }
}

