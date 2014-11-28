//#include <avr/../inttypes.h>
#include <inttypes.h>

/************************************************************************
   Data Structure:    Timer
   Author:            Cody Lundie & Deepak Parajuli
   Description:       struct for initializing timer registers
   Parameters:        N/A
 ************************************************************************/
typedef struct timer_config
{
    uint8_t number;
    uint8_t controlA;
    uint8_t controlB;
    uint8_t controlC;
    uint8_t Tcount;
    uint8_t TImask;
    uint16_t Tcount16;
    uint8_t OCR8A;
    uint8_t OCR8B;
    uint16_t OCR16A;
    uint16_t OCR16B;
    uint16_t OCR16C;
    uint16_t ICR16;
}Timer;

void configure_timer( Timer *TMR );



