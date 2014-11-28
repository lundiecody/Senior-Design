#include <avr/io.h>
#include <avr/delay.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include "timer.h"
#include "timer.c"

//Prototypes
void PWM_init();
void PWMwrite(int Rduty, int Gduty, int Bduty);
void us_delay(long int us);

//Globals
volatile int row_index = 0;

//Defines and Macros

  //PWM Timer register values
#define  CTRLA      0xAA    //Fast PWM, No prescale, Clear Output Compare on match, Top defined in ICR
#define  CTRLB      0x19
#define  DEF        0x00    //Default setup
#define  TOP        1332    //TOP value. Resets counter every 83.33 us (~12 KHz PWM)

  //Interrupt Timer register values

int main()
{
  //Global interrupts enabled
  sei();
  
  //Initialize low level modules
  Interrupt_init();
  PWM_init();
 
  while(1)
 {  
  
    PWMwrite(TOP,TOP,600);
    us_delay(500);
    PWMwrite(TOP,TOP,TOP);
    us_delay(1000);
    PWMwrite(TOP,800,TOP);
    us_delay(500);
    PWMwrite(TOP,TOP,TOP);
    us_delay(1000);
    PWMwrite(600,TOP,TOP);
    us_delay(500);
    PWMwrite(TOP,TOP,TOP);
    us_delay(1000);
 }

  return -1; 
}




//Function Definitions

void Interrupt_init()
{
  //Instantiate Timer object
  Timer TMR1;
  
  //Setup up timer Registers
  TMR1.number = 1;            //Use Timer 1
  TMR1.controlA = 0x00;       //
  TMR1.controlB = 0x01;
  TMR1.controlC = DEF;       
  TMR1.TImask = 0x01;
  TMR1.Tcount16 = 59535;
  
   //Load timer Registers
  configure_timer(&TMR1); 
}

void PWM_init()
{
  //Set PORT E to OUTPUT
  DDRE = 0xFF;
  //Instantiate timer object
  Timer TMR3;
  //Setup up timer Registers
  TMR3.number = 3;            //Use Timer 3
  TMR3.controlA = CTRLA;       //Fast PWM, No prescale, Clear Output Compare on match, Top defined in ICR
  TMR3.controlB = CTRLB;
  TMR3.controlC = DEF;       
  TMR3.TImask = DEF;
  TMR3.ICR16 = TOP;           //TOP value. Resets counter every 83.33 us (~12 KHz PWM)
  TMR3.OCR16A = TOP;
  TMR3.OCR16B = TOP;
  TMR3.OCR16C = TOP;
  
   //Load timer Registers
  configure_timer(&TMR3);
}

void PWMwrite(int Rduty, int Gduty, int Bduty)
{
  if(Rduty > TOP)
    Rduty = TOP;
  if(Gduty > TOP)
    Gduty = TOP;
  if(Bduty > TOP)
    Bduty = TOP;
    
  OCR3A = Bduty;
  OCR3B = Rduty;
  OCR3C = Gduty;
}

void us_delay(long int us)
{
  int i;
  for(i = 0; i < us; i++)
  {
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
  }
}

void loadRegisters(uint8_t* arr)
{
  uint8_t i;
  
  for( i = 0; i < 32; i++)
  {
    //Get serial input
    PORTG &= 0xFB;        //Clear the bit 2 
    PORTG |= arr[i];
    //Toggle SRCLK HIGH (Clk in input to serial registers)
    PORTG |= 0x02;
    //Toggle SRCLK LOW
    PORTG &= 0xFD;
      
  }
}

//Timer 1 overflow interrupt. ISR initiated every 375 us.
ISR(TIMER1_OVF_vect)
{
  //Start the counter at 6000 counts less than TOP. 
  TCNT1 = 59535;
  //Latch serial register values to output
  PORTD ^= 0x80;
  PORTD ^= 0x80;
  
  row_index += 1;
  if(row_index > 31)
    row_index = 0;
}

