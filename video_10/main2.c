#define F_CPU 8000000


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 255;
	PORTB = 255;

	while(1)
	{
		_delay_ms(150);
		PORTB ^=0b11111111;
	}
}