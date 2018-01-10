// Program for Slave mode
#include<avr/io.h>
#include<util/delay.h>
#include <compat/twi.h>
#include <avr/interrupt.h>

#define LCD_PORT PORTB

void TWI_init_slave(char adr);

unsigned char write_data,recv_data, adrTemp;

SIGNAL(TWI_vect)
{
	//static unsigned char i2c_state;
	unsigned char twi_status;
	// Disable Global Interrupt
	cli();
	// Get TWI Status Register, mask the prescaler bits (TWPS1,TWPS0)
	twi_status=TWSR & 0xF8;

	switch(twi_status) {
	/////recive from master//////////
	case TW_START:
	case TW_SR_SLA_ACK:      // 0x60: SLA+W received, ACK returned

	adrTemp = TWDR;      // Save data to the register address

	TWCR |= (1<<TWINT);    // Clear TWINT Flag

	break;
	case TW_SR_DATA_ACK:     // 0x80: data received, ACK returned

	recv_data = TWDR;      // Save to the register data

	TWCR |= (1<<TWINT);    // Clear TWINT Flag
	break;
	case TW_SR_STOP:         // 0xA0: stop or repeated start condition received while selected

	TWCR |= (1<<TWINT);    // Clear TWINT Flag
	break;

	//transmit to master/////////

	//case TW_ST_SLA_ACK:      // 0xA8: SLA+R received, ACK returned
	//case TW_ST_DATA_ACK:     // 0xB8: data transmitted, ACK received
	//case TW_ST_DATA_NACK:    // 0xC0: data transmitted, NACK received
	//case TW_ST_LAST_DATA:    // 0xC8: last data byte transmitted, ACK received
	//case TW_BUS_ERROR:       // 0x00: illegal start or stop condition
	default:
	TWCR |= (1<<TWINT);    // Clear TWINT Flag

	}
	// Enable Global Interrupt
	sei();
}

int main(void)
{
	DDRB=0xff;
	DDRA = 0;
	PORTA = 255;
	TWI_init_slave(0x22); // Function to initilaize slave

	// Start Slave Listening: Clear TWINT Flag, Enable ACK, Enable TWI, TWI Interrupt Enable
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE);
	TWDR = 0x00;                 // Default Initial Value


	// Enable Global Interrupt
	sei();

	//_delay_ms(150);
	while(1)
	{
		if(bit_is_clear(PINA,PA0 )) {
			TWI_init_slave(0x20); // Function to initilaize slave

		}
		if(bit_is_clear(PINA,PA1 )) {
			TWI_init_slave(0x22); // Function to initilaize slave

		}
		if(bit_is_clear(PINA,PA2 )) {
			TWI_init_slave(0x24); // Function to initilaize slave

		}
		if(bit_is_clear(PINA,PA3 )) {
			TWI_init_slave(0x26); // Function to initilaize slave

		}

		switch (recv_data)
		{
			case 0: LCD_PORT=0b11000000;break;
			case 1: LCD_PORT=0b11111001;break;
			case 2: LCD_PORT=0b10100100;break;
			case 3: LCD_PORT=0b10110000;break;
			case 4: LCD_PORT=0b10011001;break;
			case 5: LCD_PORT=0b10010010;break;
			case 6: LCD_PORT=0b10000010;break;
			case 7: LCD_PORT=0b11111000;break;
			case 8: LCD_PORT=0b10000000;break;
			case 9: LCD_PORT=0b10010000;break;
			default: LCD_PORT=255;break;
		}

	}
}

void TWI_init_slave(char adr) // Function to initilaize slave
{
	TWAR=adr & 0xFE; // Fill slave address to TWAR
	//      TWDR = 0x00; // Default Initial Value

}

