#include <avr/io.h>
#include <stdlib.h>

#define LCD_PORT PORTD  //tu konfigurujemy PORT wyswietlacza
#define TRANZYSTOR_PORT  PORTB //tu konfigurujemy PORT tranzystorów

#define LCD_DDR DDR(LCD_PORT)
#define TRANZYSTOR_DDR DDR(TRANZYSTOR_PORT)
#define DDR(x)  _SFR_IO8(_SFR_IO_ADDR(x) - 1)

void start_7ser ();
int print_7seg(int liczba, int tranzystor);