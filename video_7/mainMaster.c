#include <avr/io.h>
void Inicjacja_spi()
{
	SPCR = ( 1 << SPE ) | ( 1 << MSTR ) | ( 1 << SPR1 ) | ( 1 << SPR0 );
}
void Wyslij_spi(int8_t bajt)
{
	SPDR = bajt;
	while( ! bit_is_set( SPSR, SPIF ) );
}
int main(void)
{
	DDRB = 255; 
	PORTB = 0; 
	Inicjacja_spi();
	while (1)
	{
		if(bit_is_clear(PIND,PD0)){
			Wyslij_spi(2);
		}
		if(bit_is_clear(PIND,PD1)){
			Wyslij_spi(1);
		}
	}
}