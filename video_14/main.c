#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
        DDRA = 255;
        PORTA = 255;

        DDRC = 255;
        PORTC = 255;

    while (1)
    {
                PORTA = 0;
                for(int i=0;i<32;i++){
                        PORTC = 0;
                        PORTC = 255;
                }
                //Dioda 1
                PORTA = 255;
                for(int i=0;i<8;i++){
                        PORTC = 0;
                        PORTC = 255;
                }

                //niebieska
                PORTA = 0;
                for(int i=0;i<8;i++){
                        PORTC = 0;
                        PORTC = 255;
                }
                //zielona
                PORTA = 0;
                for(int i=0;i<8;i++){
                        PORTC = 0;
                        PORTC = 255;
                }
                //czerwona
                PORTA = 255;
                for(int i=0;i<8;i++){
                        PORTC = 0;
                        PORTC = 255;
                }
                //Dioda 2
                PORTA = 255;
                for(int i=0;i<8;i++){
                        PORTC = 0;
                        PORTC = 255;
                }
                PORTA = 0;
                //niebieska
                for(int i=0;i<8;i++){
                        PORTC = 0;
                        PORTC = 255;
                }
                //zielona
                PORTA = 255;
                for(int i=0;i<8;i++){
                        PORTC = 0;
                        PORTC = 255;
                }
                //czerwona
                PORTA = 0;
                for(int i=0;i<8;i++){
                        PORTC = 0;
                        PORTC = 255;
                }
                //koniec
                PORTA = 255;
                for(int i=0;i<32;i++){
                        PORTC = 0;
                        PORTC = 255;
                }
    }
}