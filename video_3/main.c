#include <avr/io.h>
#include <stdlib.h>
#include <util/delay_basic.h>

#include "LCD7seg.h"

int main(void)
{
start_7ser();
    while(1)
    {
	print_7seg(1,1);
	print_7seg(2,0);
    }
}
