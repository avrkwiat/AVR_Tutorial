#include <avr/io.h>
#include <stdlib.h>
#include <util/delay_basic.h>
void print_char(char znak){
   _delay_loop_2(15000);
   if (bit_is_set(UCSRA,UDRE))
   {
     UDR=znak;
    loop_until_bit_is_set(UCSRA,TXC);
   }
}

int main(void)
{
  UBRRL = 51;  //predkosc 9600 uart przy 8MHz
  //UCSRB |=0b00001000;
  //UCSRB |=0b10000110 ;
  UCSRB =_BV(TXEN); //Enable TX
  UCSRC |= (1<<URSEL)|(3<<UCSZ0); //8-bitowe    s³owo, brak parzystoœci, 1stop
  while(1)
    {
		_delay_loop_2(15000);
		print_char('A');
		print_char('V');
		print_char('R');
		UDR=0x0D;
		UDR=0x0A;
    }
}
