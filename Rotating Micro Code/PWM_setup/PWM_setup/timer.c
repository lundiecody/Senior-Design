/************************************************************************
   Program:         timer.c
   Author:          Cody Lundie and Deepak Parajuli
   Class:           CENG 447/547 - Embedded Systems
   Instructor:      Dr. Randy Hoover
   TA:              William Sorenson
   Date:            3/11/2013
   Description:     Definition of timer configuration function. Assigns
                    values in the Timer struct to the appropriate timer's
                    registers. Allows user select from timers 0,1,3,4,5.

   Input:           Timer struct
   Output:          Displays the sensor packet data sent from OI, received
                    by Seeeduino, and decoded for display by this program
                    
   Compilation instructions: 
                    Code is compiled using a Makefile designed 
                    around the ATMega1280 microcontroller.
                    
   Usage:           Timer setup for counting, PWM, and waveform generation
 
   Modifications:
   Date                Comment            
   ----    ------------------------------------------------
   3-11-13      Function written for Timer0 only. We feel a comprehensive
                configuration should be able to set up both the 8-bit and
                16-bit timers.
                        
   3-18-13      Expanded the function to set up 16-bit timers as well as
                Timer0. Not tested for 16-bit functionality. 
 ************************************************************************/
 
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>


/************************************************************************
   Function:    configure_timer()
   Author:      Cody Lundie & Deepak Parajuli
   Description: Allows the user to configure any timers 0,1,3,4, & 5. 
                User must merely initialize the appropriate values in the 
                timer struct. 
                
                Note: Not tested for 16-bit timers. But assuming Lab 4
                is to use 16-bit timers, the functionality of this function
                will be fully tested. Verified to work for Timer0.
                
   Parameters:  void
 ************************************************************************/
void configure_timer( Timer *TMR )
{
    
    switch ( TMR -> number )
    {   
        //Timer 0 setup
        case 0:
            TCCR0A = TMR -> controlA;
            TCCR0B = TMR -> controlB; 
            TCNT0 =  TMR -> Tcount;
            TIMSK0 = TMR -> TImask;
            OCR0A = TMR -> OCR8A;
            OCR0B = TMR -> OCR8B;
            break;
        
        //Timer 1 setup    
        case 1:
            TCCR1A = TMR -> controlA;
            TCCR1B = TMR -> controlB; 
            TCCR1C = TMR -> controlC;
            TCNT1 =  TMR -> Tcount16;
            TIMSK1 = TMR -> TImask;
            OCR1A = TMR -> OCR16A;
            OCR1B = TMR -> OCR16B;
            OCR1C = TMR -> OCR16C;
            ICR1 = TMR -> ICR16;
            break;
        
        //Timer 3 setup    
        case 3:
            TCCR3A = TMR -> controlA;
            TCCR3B = TMR -> controlB; 
            TCCR3C = TMR -> controlC;
            TCNT3 =  TMR -> Tcount16;
            TIMSK3 = TMR -> TImask;
            OCR3A = TMR -> OCR16A;
            OCR3B = TMR -> OCR16B;
            OCR3C = TMR -> OCR16C;
	    ICR3 = TMR -> ICR16;
         
            break;
            
         //Timer 4 setup  
         case 4:
            TCCR4A = TMR -> controlA;
            TCCR4B = TMR -> controlB; 
            TCCR4C = TMR -> controlC;
            TCNT4 =  TMR -> Tcount16;
            TIMSK4 = TMR -> TImask;
            OCR4A = TMR -> OCR16A;
            OCR4B = TMR -> OCR16B;
            OCR4C = TMR -> OCR16C;
            break;
        
        //Timer 5 setup    
        case 5:
            TCCR5A = TMR -> controlA;
            TCCR5B = TMR -> controlB; 
            TCCR5C = TMR -> controlC;
            TCNT5 =  TMR -> Tcount16;
            TIMSK5 = TMR -> TImask;
            OCR5A = TMR -> OCR16A;
            OCR5B = TMR -> OCR16B;
            OCR5C = TMR -> OCR16C;
            break;
    }

} 
