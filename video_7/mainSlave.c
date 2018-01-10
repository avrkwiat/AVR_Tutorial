#include <avr/io.h>

int main(void)
{
	DDRD = 255;
	PORTD = 255;
	DDRB = 0;
	PORTB = 0;
	SPCR = ( 1 << SPE );
	while (1) 
	{
		while ( ! bit_is_set( SPSR, SPIF ) );
		if(SPDR==2){
			PORTD&=11111110;
		}else{
			PORTD|=00000001;
		}
	}
}