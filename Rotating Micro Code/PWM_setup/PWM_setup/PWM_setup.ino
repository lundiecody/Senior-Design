#include <avr/io.h>
#include <avr/delay.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include "timer.h"
#include "timer.c"

void PWM_init();
void PWMwrite(int Rduty, int Gduty, int Bduty);
void us_delay(long int us);

#define  CTRLA      0xAA    //Fast PWM, No prescale, Clear Output Compare on match, Top defined in ICR
#define  CTRLB      0x19
#define  DEF        0x00    //Default setup
#define  TOP        1332    //TOP value. Resets counter every 83.33 us (~12 KHz PWM)

volatile int intCount = 0;
volatile int delta = 1;
int main()
{
  //Global interrupts enabled
  sei();
  //DDRB = 0xFF;
  
//  Timer TMR1;
//  //Setup up timer Registers
//  TMR1.number = 1;            //Use Timer 3
//  TMR1.controlA = CTRLA;       //Fast PWM, No prescale, Clear Output Compare on match, Top defined in ICR
//  TMR1.controlB = CTRLB;
//  TMR1.controlC = DEF;       
//  TMR1.TImask = 0x21;
//  TMR1.ICR16 = 0xFFFF;           //16 clocks per us * 375 us = 6000 clocks until interrupt
//  TMR1.OCR16A = 0xFFFF;
//  TMR1.OCR16B = 0x0000;
//  TMR1.OCR16C = 0x0000;
  
   //Load timer Registers
  //configure_timer(&TMR1);
  
  //Initialize Timer 3 for RGB PWM signals
  PWM_init();
  DDRH = 0xFF;
  PORTH = 0xFF;

  while(1)
  {
      PWMwrite(TOP,TOP, 1000);
//    if(intCount == 0)
//    {
//      PWMwrite(TOP,TOP, 1200);
//    }
//    if(intCount >= 13333 )
//    {
//      PWMwrite(TOP,TOP, TOP);
//    }
  
  }
  
  //Bad 
  return -1;
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


ISR(TIMER1_OVF_vect)
{
  TCNT1 = 0x00;
  //PORTH ^= 0xFF;
   
  //Latch Serial Register to Output pins
}

