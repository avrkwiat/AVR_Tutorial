#include <avr/io.h>
#include <avr/interrupt.h>   

SIGNAL(ADC_vect)
{
	OCR2 = ADCH; 
}

int main(void)
{
	DDRD = 255; 
	PORTD = 255; 
	ADMUX = _BV(REFS0)|_BV(REFS1)|_BV(ADLAR) ;             
	ADCSRA = _BV(ADEN)|_BV(ADIE)|_BV(ADPS2)|_BV(ADPS1)|_BV(ADPS0);
	TCCR2 = (1<<COM21)|(1<<WGM20)|(1<<WGM21)|(1<<CS20); 
	TCNT2=0;
	sei();     
	while (1) 
	{
		ADCSRA |= 1<<ADSC; 
	}
}