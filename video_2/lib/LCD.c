#include "LCD.h"


volatile uint8_t LCD_pos;

void delay_us(uint16_t us)
{
  uint16_t delay_loops;
  register uint16_t i;
  delay_loops = (us>>3)*CYCLES_PER_US;
  for (i = 0; i < delay_loops; i++)
  {
    asm volatile ("WDR"::);
    asm volatile ("NOP"::);
  }
}


void delay_ms(uint16_t count)
{
  while (count--)
    {
     delay_us(1000);
     //sbi(PORTA,4);cbi(PORTA,4);
    }
}

/*///////////////////////////////////////////////////
	Funkcja zapisu 4 bitow do wyswietlacza
///////////////////////////////////////////////////*/
void LCD_clock(uint8_t data, uint8_t rs)
{
 	LCD_DDR |= 0x0F | _BV(LCD_EN) | _BV(LCD_RS) | _BV(LCD_RW);
 	cbi(LCD_PORT, LCD_RW);
 	if (rs == 1)
    	sbi(LCD_PORT, LCD_RS);      		//zapis danych
 	else
    	cbi(LCD_PORT, LCD_RS);				//zapis komendy
 	LCD_PORT = ((data) | (LCD_PORT & 0xF0));//wyslanie danych na dolna polowke portu D 
 	sbi(LCD_PORT, LCD_EN);					//ustawienie wysokiego zbocza na lini E
 	delay_us(20);
 	cbi(LCD_PORT, LCD_EN);					//ustawienie niskiego zbocza na lini E - potwierdzenie zapisu
 	delay_us(20);
	cbi(LCD_PORT, LCD_RS);
 	sbi(LCD_PORT, LCD_RW);
}

/*///////////////////////////////////////////////////
	Funkcja podzialu bajtu na dwie polowki, 
	przeslanie starszej polowki jako pierwszej
///////////////////////////////////////////////////*/
void LCD_send(uint8_t data, uint8_t rs)
{
  	LCD_clock(data >> 4, rs);				//przesowamy gorna polowke na do³ i wysy³amy
  	LCD_clock(data & 0x0F, rs);				//wysy³amy dolna polowke
}

/*///////////////////////////////////////////////////
	Funkcja zapisu komendy
///////////////////////////////////////////////////*/
void LCD_send_0(uint8_t ch)
{
  	LCD_send(ch, 0);
}

/*///////////////////////////////////////////////////
	Funkcja zapisu danych
///////////////////////////////////////////////////*/
void LCD_send_1(uint8_t ch)
{
  	LCD_send(ch, 1);
}

/*///////////////////////////////////////////////////
	Funkcja ustawienia pozycji kursora
///////////////////////////////////////////////////*/
void LCD_xy(uint8_t x, uint8_t y)
{
  	switch(y)
  	{
		#if (LCD_Y > 1)
    		case 1: y=0x40; break;
		#endif
		#if (LCD_Y>2)
   			 case 2: y=0x14; break;
		#endif
		#if (LCD_Y>3)
   			 case 3: y=0x54; break;
		#endif
  	}
  	LCD_send_0(0x80+y+x);
}

/*///////////////////////////////////////////////////
	Funkcja czyszczenie wyswietlacza
///////////////////////////////////////////////////*/
void LCD_clear(void)
{
  	LCD_send_0(0x01);
  	delay_ms(3);
  	LCD_xy(0, 0);
}

/*///////////////////////////////////////////////////
	Funkcja inicjalizacji wyswietlacza
///////////////////////////////////////////////////*/
void LCD_start(void)
{
  	register uint8_t i;
  	LCD_DDR |= 0x0F | _BV(LCD_EN) | _BV(LCD_RS);
  	delay_ms(50);
  	for(i = 0; i < 3; i++)
  	{
    	LCD_clock(0x03, 0);
    	delay_ms(25);
  	}
  	LCD_clock(0x02, 0);
  	LCD_send_0(0x2C);
  	LCD_send_0(0x08);
  	LCD_clear();
  	LCD_send_0(0x06);
  	LCD_send_0(0x0C);
}

/***************************************************/
/*    Wyswietla znak podany w parametrze funkcji   */
/*                                                 */
/***************************************************/

void LCD_putchar(char ch)
{
  LCD_send_1(ch);
}


/***************************************************/
/*    Wyswietla liczbe 8 bitów bez znaku podana    */
/*  w parametrze funkcji, x,y - wspolzedne na LCD  */
/***************************************************/
#ifdef LCD_DEC2
void LCD_dec2(uint8_t bajt)
{
 LCD_send_1(bajt/10+0x30);
 LCD_send_1(bajt%10+0x30);
}
#endif

/***************************************************/
/*    Wyswietla liczbe 8 bitów bez znaku podana    */
/*  w parametrze funkcji, x,y - wspolzedne na LCD  */
/***************************************************/
//#ifdef LCD_UINT8
void LCD_uint8xy(uint8_t bajt, uint8_t x, uint8_t y)
{
 register uint8_t znak, i;
 LCD_xy(x+2,y);
 if(!bajt)
         LCD_send_1(0x30);
 else
         {
          LCD_cursor_down();
          for(i=0;i<3;i++)
                {
	     if(bajt)
	            {
		 znak=bajt%10;
		 bajt/=10;
		 LCD_send_1(znak+0x30);
		}
	    }
          LCD_cursor_up();
          LCD_xy(x+3,y);
         }
}
//#endif

/***************************************************/
/*   Wyswietla liczbe 16 bitów bez znaku podana    */
/*  w parametrze funkcji, x,y - wspolzedne na LCD  */
/***************************************************/
//#ifdef LCD_UINT16
void LCD_uint16xy(uint16_t slowo, uint8_t x, uint8_t y)
{
 register uint8_t znak, i;
 LCD_xy(x+4,y);
 if(!slowo)
         LCD_send_1(0x30);
 else
         {
          LCD_cursor_down();
          for(i=0;i<5;i++)
		 {
		  if(slowo)
		          {
		           znak=slowo%10;
		           slowo/=10;
		           LCD_send_1(znak+0x30);
		          }
		 }
	 LCD_cursor_up();
	 LCD_xy(x+5,y);
         }
}
//#endif

/***************************************************/
/*    Wyswietla liczbe 32 bity bez znaku podana    */
/*  w parametrze funkcji, x,y - wspolzedne na LCD  */
/***************************************************/
#ifdef LCD_UINT32
void LCD_uint32xy(uint32_t slowo, uint8_t x, uint8_t y)
{
 register uint8_t znak, i;
 LCD_xy(x+9,y);
 if(!slowo)
         LCD_send_1(0x30);
 else
         {
          LCD_cursor_down();
          for(i=0;i<10;i++)
		 {
		  if(slowo)
		          {
		           znak=slowo%10;
		           slowo/=10;
		           LCD_send_1(znak+0x30);
		          }
		 }
	 LCD_cursor_up();
	 LCD_xy(x+10,y);
         }
}
#endif

/***************************************************/
/*   Wyswietla liczbe 8 bitów ze znakiem podana    */
/*  w parametrze funkcji, x,y - wspolzedne na LCD  */
/***************************************************/
#ifdef LCD_INT8
void LCD_int8xy(int8_t bajt, uint8_t x, uint8_t y)
{
 register int8_t modul;
 register uint8_t znak, i;
 uint8_t minus=0;
 modul=bajt;
 if(modul>>7)
              {
	   minus=1;
	   modul=~(int8_t)(modul);
	   modul++;
	  }
 LCD_xy(x,y);
 for(i=0;i<4;i++)
                LCD_send_1(' ');
 LCD_xy(x+3,y);
 if(!modul)
          LCD_send_1(0x30);
 else
          {
           LCD_cursor_down();
           for(i=0;i<3;i++)
                {
	     if(modul)
	            {
		 znak=(uint8_t)modul%10;
		 modul=(uint8_t)modul/10;
		 LCD_send_1(znak+0x30);
		}
	    }
           if(minus)
                   LCD_send_1('-');
           else
                   LCD_send_1(' ');
           LCD_cursor_up();
           LCD_xy(x+4,y);
          }
}
#endif

/***************************************************/
/*   Wyswietla liczbe 16 bitów ze znakiem podana   */
/*  w parametrze funkcji, x,y - wspolzedne na LCD  */
/***************************************************/

void LCD_int16xy(int16_t slowo, uint8_t x, uint8_t y)
{
 uint8_t znak, i;
 uint8_t minus=0;
 if(slowo>>15)
              {
	   minus=1;
	   slowo=~slowo;
	   slowo++;
	  }
 LCD_xy(x,y);
 for(i=0;i<6;i++)
                LCD_send_1(' ');
 LCD_xy(x+5,y);
 if(!slowo)
          LCD_send_1(0x30);
 else
          {
           LCD_cursor_down();
           for(i=0;i<5;i++)
                {
	     if(slowo)
	            {
		 znak=slowo%10;
		 slowo/=10;
		 LCD_send_1(znak+0x30);
		}
	    }
           if(minus)
                   LCD_send_1('-');
           else
                   LCD_send_1(' ');
           LCD_cursor_up();
           LCD_xy(x+6,y);
          }
}


/***************************************************/
/*    Wyswietla liczbe 32 bity ze znakiem podana   */
/*  w parametrze funkcji, x,y - wspolzedne na LCD  */
/***************************************************/

void LCD_int32xy(int32_t slowo, uint8_t x, uint8_t y)
{
 uint8_t znak, i;
 uint8_t minus=0;
 if(slowo>>31)
              {
	   minus=1;
	   slowo=~slowo;
	   slowo++;
	  }
 LCD_xy(x,y);
 for(i=0;i<10;i++)
                LCD_send_1(' ');
 LCD_xy(x+10,y);
 if(!slowo)
          LCD_send_1(0x30);
 else
          {
           LCD_cursor_down();
           for(i=0;i<10;i++)
                {
	     if(slowo)
	            {
		 znak=slowo%10;
		 slowo/=10;
		 LCD_send_1(znak+0x30);
		}
	    }
           if(minus)
                   LCD_send_1('-');
           else
                   LCD_send_1(' ');
           LCD_cursor_up();
           LCD_xy(x+11,y);
          }
}


/*///////////////////////////////////////////////////
	Funkcja wyswietlania tekstu na wyswietlaczu
///////////////////////////////////////////////////*/

void LCD_putstr(char* s)
{
  	register char c;
  	while ((c = *s++))
    	LCD_send_1(c);
}


/*///////////////////////////////////////////////////
	Funkcja wyswietlania tekstu na wyswietlaczu 
	w miejscu x, y
///////////////////////////////////////////////////*/
void LCD_putstrxy(char* s, uint8_t x, uint8_t y)
{
  	register char c;
  	LCD_xy(x,y);
  		while ((c = *s++))
    LCD_send_1(c);
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
