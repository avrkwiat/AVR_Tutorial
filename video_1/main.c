#include <avr/io.h>
#include <util/delay_basic.h>
int main(void)
{
	DDRD = 0b00000000;
	DDRB = 255;
	PORTB = 255;
	PORTD = 0xFF;
	while(1)
	{
		if(bit_is_clear(PIND,PD6 ))
		{
			_delay_loop_1(150);
			PORTB &=0b11111110;
		}
		if(bit_is_clear(PIND,PD5 ))
		{
			_delay_loop_1(150);
			PORTB |= 0b00000001;
		}
	}
}
