#include <avr/io.h>
#include <util/delay_basic.h>
#include "LCD.h"

int main(void)
{
LCD_start();
LCD_putstrxy("MARCIN", 0, 0);
LCD_putstrxy("Kwiatkowski", 0, 1);
while (1) 
{
 
}
}
