#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void int_adc();
unsigned short read_adc();
void show_adc_led(unsigned short data);

int main(void)
{
	unsigned short value;
	DDRB = 0x0F;
	DDRF = 0x00;
	init_adc();
	
	PORTB = 0x02;
	_delay_ms(3000);
	PORTB = 0x00;
	
	while (1)
	{
		PORTB |= 0x08;
		value = read_adc();
		show_adc_led(value);
	}
}

int init_adc(void)
{
	ADMUX = 0x40;
	ADCSRA = 0x87;    // adc en
}
unsigned short read_adc()
{
	unsigned char adc_low, adc_high;
	unsigned short value;

	ADCSRA |= 0x40;    // ADC start
	// ADC Complete
	while((ADCSRA & 0x10) != 0x10);
	adc_low = ADCL;
	adc_high = ADCH;
	value = (adc_high << 8) | adc_low;
	
	return value;
}

void show_adc_led(unsigned short value)
{
	if(value > 900)	PORTB = 0x01;
	else	PORTB = 0x04;
}
