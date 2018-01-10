#include <inttypes.h>
#include <avr/io.h>
#include <stdlib.h> 

#define F_CPU 8000000
#define CYCLES_PER_US (F_CPU / 1000000)

#define LCD_PORT	PORTC	//port wyswietlacza, interfejs 4 bitowy
							//podlaczenie do 4 starszych bitow 
							//Db7->PC3 
							//DB6->PC2 
							//DB5->PC2 
							//DB4->PC1 
							//DB3->PC0
#define LCD_EN		PC4		//Enable
#define LCD_RW		PC5		//R/W
#define LCD_RS		PC6		//RS

#define LCD_X		16		//Liczba znakow w linii
#define LCD_Y		2		//Liczba linii

#define LCD_DDR		DDR(LCD_PORT)
#define LCD_PIN		PIN(LCD_PORT)

#define DDR(x) _SFR_IO8(_SFR_IO_ADDR(x) - 1)
#define PIN(x) _SFR_IO8(_SFR_IO_ADDR(x) - 2)

#define sbi(sfr, bit) sfr |= 1 << bit
#define cbi(sfr, bit) sfr &= ~(uint8_t)(1 << bit)

#define LCD_cursor_off()	LCD_send(0x0C, 0)
#define LCD_cursor_on()		LCD_send(0x0F, 0)
#define LCD_cursor_right()	LCD_send(0x14, 0)
#define LCD_cursor_left()	LCD_send(0x10, 0)
#define LCD_cursor_down()	LCD_send(0x04, 0)
#define LCD_cursor_up()		LCD_send(0x06, 0)
#define VFD_100percent()	LCD_send(0x2C, 0)
#define VFD_75percent()		LCD_send(0x2D, 0)
#define VFD_50percent()		LCD_send(0x2E, 0)
#define VFD_25percent()		LCD_send(0x2F, 0)


/*
typedef union 
{
 float dana_float;
 unsigned char dana_char[4];
} float2char;

typedef union {
 int16_t dana_int16_t;
 unsigned char dana_char[2];
} int16_t2char;

typedef union {
 int32_t dana_int32_t;
 unsigned char dana_char[4];
} int32_t2char;
*/

//void delay_us(uint16_t us);
//void delay_ms(uint16_t count);
void LCD_clock(uint8_t data, uint8_t rs);
void LCD_send(uint8_t data, uint8_t rs);
void LCD_send_0(uint8_t ch);
void LCD_send_1(uint8_t ch);
void LCD_xy(uint8_t x, uint8_t y);
void LCD_clear(void);
void LCD_start(void);
void LCD_putchar(char ch);
void LCD_dec2(uint8_t bajt);
void LCD_uint8xy(uint8_t bajt, uint8_t x, uint8_t y);
void LCD_uint16xy(uint16_t slowo, uint8_t x, uint8_t y);
void LCD_uint32xy(uint32_t slowo, uint8_t x, uint8_t y);
void LCD_int8xy(int8_t bajt, uint8_t x, uint8_t y);
void LCD_int16xy(int16_t slowo, uint8_t x, uint8_t y);
void LCD_int32xy(int32_t slowo, uint8_t x, uint8_t y);
void LCD_putstr(char* s);
void LCD_putstrxy(char* s, uint8_t x, uint8_t y);








