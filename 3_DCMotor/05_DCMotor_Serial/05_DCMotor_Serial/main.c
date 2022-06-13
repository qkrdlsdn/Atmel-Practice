#define F_CPU	16000000UL
#define BAUDRATE(x)	((F_CPU / 16 / x) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int USART1_len=0;
int USART1_rx_end=0;
unsigned char Rx_Buffer[200];

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
	DDRD = 0x00;
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
	if ((PIND&index) == 0x00)
	{
		return 1;
	}
	return 0;
}

void uart_init(unsigned int baud)
{
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char)baud;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0) |
	(1 << RXCIE0);
}

void uart_write(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

int main(void)
{
	int speed = 0;
	Port_Init();
	
	uart_init(BAUDRATE(9600));
	sei();	
	
	while(1)
	{
		// up
		if(Btn_click(0x01))
		{
			while(Btn_click(0x01));
			
			if(speed/10 < 6)	speed = 60;
			else	speed = ((speed/10)*10)+10;
		}
		//down
		if(Btn_click(0x02))
		{
			while(Btn_click(0x02));
			if(speed/10 <= 6) speed = 0;
			else	speed = ((speed/10)*10)-10;
		}
		//stop
		if(Btn_click(0x04))
		{
			while(Btn_click(0x04));
			speed = 0;
		}
		//uart
		if(USART1_rx_end == 1)
		{
			USART1_rx_end = 0;
			//USART1_len = 0;
			
			if(Rx_Buffer[1]=='0')speed = 0;
			else if(Rx_Buffer[1]=='6')speed = 60;
			else if(Rx_Buffer[1]=='7')speed = 70;
			else if(Rx_Buffer[1]=='8')speed = 80;
			else if(Rx_Buffer[1]=='9')speed = 90;
			else if(Rx_Buffer[1]=='1')speed = 100;
			
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
		//uart_send(speed);
	}
}

ISR(USART0_RX_vect)
{
	static uint8_t usart1_chk=0;
	unsigned char buf = UDR0;
	
	USART1_rx_end=0;
	switch(usart1_chk)
	{
		case 0:
		if(buf ==0x02){
			Rx_Buffer[USART1_len]= buf;
			USART1_len++;
			usart1_chk=1;
		}
		else usart1_chk=0;
		break;
		case 1:
		Rx_Buffer[USART1_len]= buf;
		USART1_len++;
		
		if(buf ==0x03){
			USART1_rx_end=1;
			usart1_chk=0;
			USART1_len=0;
		}
		break;
		default :
		usart1_chk=0;
		break;
	}
	
}