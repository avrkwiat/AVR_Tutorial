// Program for Master Mode
// Check Code2 for Slave Mode Program
#include<avr/io.h>
#include<util/delay.h>
#include<inttypes.h>

void TWI_start(void);
void TWI_repeated_start(void);
void TWI_init_master(void);
void TWI_write_address(unsigned char);
void TWI_read_address(unsigned char);
void TWI_write_data(unsigned char);
void TWI_read_data(void);
void TWI_stop(void);

unsigned char address=0x20, read=1, write=0;
unsigned char write_data=0x01, recv_data;

int main(void)
{
	_delay_ms(2000);
	DDRB=0xff;
	TWI_init_master();  // Function to initialize TWI
	while(1)
	{
		write_data=0;
		TWI_start(); // Function to send start condition
		TWI_write_address(address+write); // Function to write address and data direction bit(write) on SDA
		TWI_write_data(write_data);      // Function to write data in slave
		TWI_stop(); // Function to send stop condition


		_delay_ms(10); // Delay of 10 mili second

		TWI_start();
		TWI_read_address(address+read); // Function to write address and data direction bit(read) on SDA
		TWI_read_data(); // Function to read data from slave
		TWI_stop();

		write_data=1;
		TWI_start(); // Function to send start condition
		TWI_write_address(address+2+write); // Function to write address and data direction bit(write) on SDA
		TWI_write_data(write_data);      // Function to write data in slave
		TWI_stop(); // Function to send stop condition


		_delay_ms(10); // Delay of 10 mili second

		TWI_start();
		TWI_read_address(address+2+read); // Function to write address and data direction bit(read) on SDA
		TWI_read_data(); // Function to read data from slave
		TWI_stop();

		write_data=2;
		TWI_start(); // Function to send start condition
		TWI_write_address(address+4+write); // Function to write address and data direction bit(write) on SDA
		TWI_write_data(write_data);      // Function to write data in slave
		TWI_stop(); // Function to send stop condition


		_delay_ms(10); // Delay of 10 mili second

		TWI_start();
		TWI_read_address(address+4+read); // Function to write address and data direction bit(read) on SDA
		TWI_read_data(); // Function to read data from slave
		TWI_stop();

		write_data=4;
		TWI_start(); // Function to send start condition
		TWI_write_address(address+6+write); // Function to write address and data direction bit(write) on SDA
		TWI_write_data(write_data);      // Function to write data in slave
		TWI_stop(); // Function to send stop condition


		_delay_ms(10); // Delay of 10 mili second

		TWI_start();
		TWI_read_address(address+6+read); // Function to write address and data direction bit(read) on SDA
		TWI_read_data(); // Function to read data from slave
		TWI_stop();

		_delay_ms(1000);

		//write_data = write_data * 2;
	}


}

void TWI_init_master(void) // Function to initialize master
{
	TWBR=0x01; // Bit rate
	TWSR=(0<<TWPS1)|(0<<TWPS0); // Setting prescalar bits
	// SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
}

void TWI_start(void)
{

	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	int i=0;
	while(!(TWCR & (1<<TWINT))){i++;_delay_ms(10); if(i>10)break;}; // Wait till start condition is transmitted
	i=0;
	while((TWSR & 0xF8)!= 0x08){i++;_delay_ms(10); if(i>10)break;}; // Check for the acknowledgement
}

void TWI_repeated_start(void)
{
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	int i=0;
	while(!(TWCR & (1<<TWINT))){i++;_delay_ms(10); if(i>10)break;}; // wait till restart condition is transmitted
	i=0;
	while((TWSR & 0xF8)!= 0x10){i++;_delay_ms(10); if(i>10)break;}; // Check for the acknoledgement
}

void TWI_write_address(unsigned char data)
{
	TWDR=data; // Address and write instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	int i=0;
	while (!(TWCR & (1<<TWINT))){i++;_delay_ms(10); if(i>10)break;}; // Wait till complete TWDR byte transmitted
	i=0;
	while((TWSR & 0xF8)!= 0x18){i++;_delay_ms(10); if(i>10)break;};  // Check for the acknoledgement
}

void TWI_read_address(unsigned char data)
{
	TWDR=data; // Address and read instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	int i=0;
	while (!(TWCR & (1<<TWINT))){i++;_delay_ms(10); if(i>10)break;}; // Wait till complete TWDR byte received
	i=0;
	while((TWSR & 0xF8)!= 0x40){i++;_delay_ms(10); if(i>10)break;};  // Check for the acknoledgement
}

void TWI_write_data(unsigned char data)
{
	TWDR=data; // put data in TWDR
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	int i=0;
	while (!(TWCR & (1<<TWINT))){i++;_delay_ms(10); if(i>10)break;}; // Wait till complete TWDR byte transmitted
	i=0;
	while((TWSR & 0xF8) != 0x28){i++;_delay_ms(10); if(i>10)break;}; // Check for the acknoledgement
}

void TWI_read_data(void)
{
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	int i=0;
	while (!(TWCR & (1<<TWINT))){i++;_delay_ms(10); if(i>10)break;}; // Wait till complete TWDR byte transmitted
	i=0;
	while((TWSR & 0xF8) != 0x58){i++;_delay_ms(10); if(i>10)break;}; // Check for the acknoledgement
	recv_data=TWDR;
	PORTB=recv_data;
}

void TWI_stop(void)
{
	// Clear TWI interrupt flag, Put stop condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	int i=0;
	while(!(TWCR & (1<<TWSTO))){i++;_delay_ms(10); if(i>10)break;};  // Wait till stop condition is transmitted
}