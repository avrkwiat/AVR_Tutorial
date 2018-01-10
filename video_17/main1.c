#include <avr/io.h>

int main(void)
{
    int liczba = 0;
        DDRD = 255;
        PORTD = 255;

        DDRC = 255;
        PORTC = 0;

        DDRB = 255;
        PORTB = 0;  // enable G
    while (1)
    {
                                //********** pierwszy driver ************///
                                for(int i=0;i<8;i++){
                                        if(i==3) {
                                                PORTD |= 0b00100000; //serin ustawianie 1
                                        }else PORTD &= 0b11011111; // serin resetowanie 0

                                        PORTD&= 0b01111111; // srclk
                                        PORTD|= 0b10000000; //srclk

                                }
                                //********** drugi driver ************///
                                for(int i=0;i<8;i++){
                                        PORTD &= 0b11011111; // serin resetowanie 0
                                        //PORTD |= 0b00100000; serin ustawianie 1

                                        PORTD&= 0b01111111; // srclk
                                        PORTD|= 0b10000000; //srclk

                                }
                     
                                PORTD|= 0b01000000; // rck
                                PORTD&= 0b10111111; //rck

    }
}