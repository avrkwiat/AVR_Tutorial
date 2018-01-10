#include <avr/io.h>
#include <avr/eeprom.h>

#define PAMIEC  512

uint8_t eeprom_val[PAMIEC] __attribute__((section(".eeprom")));

int main(void)
{
    eeprom_busy_wait();
    eeprom_write_byte(&eeprom_val[0],0x01);

    while (1) 
    {

    }
}