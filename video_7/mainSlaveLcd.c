#include <avr/io.h>
#include "LCD.h"

void Inicjacja_spi()
{
	SPCR = ( 1 << SPE );
}

int8_t Odbieraj_spi()
{                            
   while ( ! bit_is_set( SPSR, SPIF ) );        
   return SPDR; 
}

int main(void)
{
	DDRD = 255;
	PORTD = 255;
	DDRB = 0;
	PORTB = 0;
	Inicjacja_spi();
	LCD_start();
	LCD_clear();
	LCD_putstrxy("dziala", 1, 1);

	while (1)
	{
		LCD_int8xy(Odbieraj_spi(), 0, 0);
		if(Odbieraj_spi()==2){
			PORTD&=11111110;
		}else{
			PORTD|=00000001;
		}
		LCD_putstrxy("dziala", 1, 1);
	}
}