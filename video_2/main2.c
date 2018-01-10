#include <avr/io.h>
#include <util/delay_basic.h>
int main(void)
{
DDRD = 0b00000000;
DDRB = 0b11111111;
PORTB = 0b11111111;
PORTD = 0b11111111;
while(1)
{
if(PIND==0b11111110)
{
	_delay_loop_1(150);
	PORTB &=0b11111110;
}
if(PIND==0b11111101)
{
	_delay_loop_1(150);
	PORTB |= 0b00000001;
}
}
}
