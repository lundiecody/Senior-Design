#include <avr/io.h>
#include <avr/delay.h>
#include <util/delay.h>
#include "usart.h"
#include "usart.c"

void loadRegisters(uint16_t num);
#define F_CPU 16000000
usart_config Usart0;

int main(void)
{
  
  uint16_t num = 0x0000;
  uint16_t t2 = 0x0002;
  unsigned long t1 = 0x0000;
  
  DDRH = 0xFF;
  DDRG = 0xFF;
  DDRE = 0xFF;
  PORTH = 0x00;
  PORTG = 0x00;
  PORTE = 0x00;
  
  
  //Init usart 0 for computer communications
    Usart0.number = 0;
    Usart0.baudrate = 57600;
    
    //Actually configure USART0
    configure_usart( &Usart0 );
    
  while(1)
  {
     t1 = micros();
     loadRegisters(0x0001);  
     t2 = micros();

     //num = num + 0x0001;
     _delay_ms(1000);
     
     Serial.print('H');
     //usartNtx( 0, (int8_t)5 );
     //num += 1;
  }

}
void loadRegisters(uint16_t num)
{
  uint8_t i = 0;
  
  for( i = 0; i < 16; i++)
  {
    //Get serial input
    //PORTH = ( (num << i) & 0x8000) >> 12;
    PORTH ^= 0x08;
    //Toggle SRCLK HIGH (Clk in input to serial registers)
    PORTG ^= 0x20;
    //Toggle SRCLK LOW
    PORTG = 0x00;
      
  }
  
  //Latch serial register values to output
  PORTE ^= 0x08;
  PORTE = 0x00;
}


