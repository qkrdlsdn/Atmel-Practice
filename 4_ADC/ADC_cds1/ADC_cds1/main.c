#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

/*
#define CDS_10 341
#define CDS_20 450
#define CDS_50 550
#define CDS_80 650
#define CDS_100 731
*/

#define CDS_10	350
#define CDS_20	400
#define CDS_50	450
#define CDS_60	500
#define CDS_70	550
#define CDS_80	600
#define CDS_90	650
#define CDS_100	700

void int_adc();
unsigned short read_adc();
void show_adc_led(unsigned short data);

int main(void)
{
	unsigned short value;
	DDRC = 0xFF;
	DDRF = 0x00;
	init_adc();
	while (1)
	{
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
	
	if(value <= CDS_10)	PORTC = 0x00;
	else if(value <= CDS_20)	PORTC = 0x80;
	else if(value <= CDS_50)	PORTC = 0xc0;
	else if(value <= CDS_60)	PORTC = 0xe0;
	else if(value <= CDS_70)	PORTC = 0xf0;
	else if(value <= CDS_80)	PORTC = 0xf8;
	else if(value <= CDS_90)	PORTC = 0xfc;
	else if(value <= CDS_100)	PORTC = 0xfe;
	else PORTC = 0xff;
	
	/*
	if(value<=CDS_10) PORTC = 0x1F;
	else if(value<=CDS_20) PORTC = 0x0F;
	else if(value<=CDS_50) PORTC = 0x07;
	else if(value<=CDS_80) PORTC = 0x03;
	else if(value<=CDS_100) PORTC = 0x01;
	else PORTC = 0x00;
	*/
}