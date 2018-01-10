#include <avr/interrupt.h>
#include <avr/io.h>
SIGNAL(USART_RXC_vect)              
{
	if(UDR=='z'){
		PORTB &= 0b11111110;
	} else {
		PORTB|= 0b00000001;
	}
}

int main(void)
{
	UBRRL = 51;  //predkosc 9600 uart
	UCSRB =_BV(TXEN)|_BV(RXEN)|_BV(RXCIE);
	UCSRC |= (1<<URSEL)|(3<<UCSZ0); 
	sei();    // w³¹cz obs³ugê przerwañ
	DDRB = 255;
	PORTB = 0xFF;
	while (1)
	{
	}
}
