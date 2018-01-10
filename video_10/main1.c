#if KONTROLA == 1
	int liczba =0b11111110;
#elif KONTROLA == 2
	int liczba =0b11111100;
#elif KONTROLA == 3
	int liczba =0b11111000;
#else
#define X
#endif

#include <stdio.h>
#include <avr/io.h>

int main(void)
{
	DDRB = 255;
	PORTB = 255;
	while(1)
	{
		#if !defined(X)
		PORTB =liczba;
		#endif
	}
}