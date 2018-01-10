#include <avr/io.h>
#include <util/delay.h>
//#include <avr/wdt.h>
#include "LCD.h"

#define wdt_reset() __asm__ __volatile__ ("wdr")

int main(void)
{
	DDRB = 0; 
	PORTB = 255; 
	WDTCR |= 0b00011011;
	LCD_start();
	LCD_clear();
	while (1) 
	{
		wdt_reset();
		if(bit_is_clear(PINB,PB6 ))  
		{
			LCD_putstrxy("Petla nop 1sek ", 0, 0); 
			_delay_ms(1500);
		}
		if(bit_is_clear(PINB,PB5 ))
		{
			LCD_putstrxy("Petla 0,014s  ", 0, 0);
			_delay_ms(14);
		}
		if(bit_is_clear(PINB,PB4 ))
		{
			LCD_putstrxy("wylaczyles watch", 0, 0);
			_delay_ms(14);
			wdt_reset();
			WDTCR |= (1<<WDTOE) | (1<<WDE);
			WDTCR = 0x00;
		}

	}
}