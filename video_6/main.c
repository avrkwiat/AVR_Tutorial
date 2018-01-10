#include <avr/interrupt.h>  
#include <avr/io.h>
#include <util/delay.h>

SIGNAL(ADC_vect)                       
{
	if(ADCH>125){
		PORTB&=0b11111110;
	}else {
		PORTB|=0b00000001;
	}
}

int main(void)
	{
		ADMUX = _BV(REFS0)|_BV(REFS1)|_BV(ADLAR) ;           
		ADCSRA = _BV(ADEN)|_BV(ADIE)|_BV(ADPS2)|_BV(ADPS1)|_BV(ADPS0); 
		DDRB=255;
		PORTB=255;
		sei();              
	while (1)
	{
		ADCSRA|=_BV(ADSC);
		_delay_ms(1500); 
	}
}