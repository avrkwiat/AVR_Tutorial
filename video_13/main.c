#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 255; //ustawiamy port B jako wyj�cie
	PORTA = 255; // ustawienie napi�cia na porcie B
	DDRD = 0b00000000; //ustawiamy port D jako wej�cie
	PORTD = 255; // pullup na Porcie D

	while (1) 
	{
		if(bit_is_clear(PIND,PD6 ))
		{
			_delay_ms(1500); 
			PORTA &=0b01111111; 
		}
		if(bit_is_clear(PIND,PD5 ))
		{
			_delay_ms(1500);
			PORTA |= 0b10000000; 
		}
	}
}