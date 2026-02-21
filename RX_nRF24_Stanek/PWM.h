
//*********************************************************************************************************************
// PWM frequency prescaler for ATmega328P and ATmega328PB
//*********************************************************************************************************************

#ifndef __PWM_h__
#define __PWM_h__

#include <Arduino.h>
#include "Config.h"

//*********************************************************************************************************************
// Pin D5 and D6 (8-bit Timer/Counter 0, functions delay, millis, micros and delayMicroseconds)
//*********************************************************************************************************************
//#define TIMER0_61HZ
//#define TIMER0_244HZ
//#define TIMER0_976HZ_DEFAULT
//#define TIMER0_7812HZ
//#define TIMER0_62500HZ

#if defined(TIMER0_61HZ)
  #define PRESCALER_TIMER0_5_6  1024
#endif
#if defined(TIMER0_244HZ)
  #define PRESCALER_TIMER0_5_6  256
#endif
#if defined(TIMER0_976HZ_DEFAULT)
  #define PRESCALER_TIMER0_5_6  64
#endif
#if defined(TIMER0_7812HZ)
  #define PRESCALER_TIMER0_5_6  8
#endif
#if defined(TIMER0_62500HZ)
  #define PRESCALER_TIMER0_5_6  1
#endif

//*********************************************************************************************************************
// Pin D9 and D10 (16-bit Timer/Counter 1, Servo library)
//*********************************************************************************************************************
//#define TIMER1_30HZ
//#define TIMER1_122HZ
//#define TIMER1_488HZ_DEFAULT
//#define TIMER1_3906HZ
//#define TIMER1_31250HZ

#if defined(TIMER1_30HZ)
  #define PRESCALER_TIMER1_9_10  1024
#endif
#if defined(TIMER1_122HZ)
  #define PRESCALER_TIMER1_9_10  256
#endif
#if defined(TIMER1_488HZ_DEFAULT)
  #define PRESCALER_TIMER1_9_10  64
#endif
#if defined(TIMER1_3906HZ)
  #define PRESCALER_TIMER1_9_10  8
#endif
#if defined(TIMER1_31250HZ)
  #define PRESCALER_TIMER1_9_10  1
#endif

//*********************************************************************************************************************
// Pin D3 and D11 (8-bit Timer/Counter 2)
//*********************************************************************************************************************
//#define TIMER2_30HZ
//#define TIMER2_122HZ
//#define TIMER2_244HZ
//#define TIMER2_488HZ_DEFAULT
//#define TIMER2_976HZ
//#define TIMER2_3906HZ
//#define TIMER2_31250HZ

#if defined(TIMER2_30HZ)
  #define PRESCALER_TIMER2_3_11  1024
#endif
#if defined(TIMER2_122HZ)
  #define PRESCALER_TIMER2_3_11  256
#endif
#if defined(TIMER2_244HZ)
  #define PRESCALER_TIMER2_3_11  128
#endif
#if defined(TIMER2_488HZ_DEFAULT)
  #define PRESCALER_TIMER2_3_11  64
#endif
#if defined(TIMER2_976HZ)
  #define PRESCALER_TIMER2_3_11  32
#endif
#if defined(TIMER2_3906HZ)
  #define PRESCALER_TIMER2_3_11  8
#endif
#if defined(TIMER2_31250HZ)
  #define PRESCALER_TIMER2_3_11  1
#endif

//*********************************************************************************************************************
// Pin D0(RX) and specific pin PD2(2) is not paired (ATmega328PB 16-bit Timer/Counter 3)
//*********************************************************************************************************************
//#define TIMER3_30HZ
//#define TIMER3_122HZ
//#define TIMER3_488HZ_DEFAULT
//#define TIMER3_3906HZ
//#define TIMER3_31250HZ

#if defined(TIMER3_30HZ)
  #define PRESCALER_TIMER3_0  1024
#endif
#if defined(TIMER3_122HZ)
  #define PRESCALER_TIMER3_0  256
#endif
#if defined(TIMER3_488HZ_DEFAULT)
  #define PRESCALER_TIMER3_0  64
#endif
#if defined(TIMER3_3906HZ)
  #define PRESCALER_TIMER3_0  8
#endif
#if defined(TIMER3_31250HZ)
  #define PRESCALER_TIMER3_0  1
#endif

//*********************************************************************************************************************
// Pin PD1(1)TX and specific pin PD2(2) (ATmega328PB 16-bit Timer/Counter 4)
//*********************************************************************************************************************
//#define TIMER4_30HZ
//#define TIMER4_122HZ
//#define TIMER4_488HZ_DEFAULT
//#define TIMER4_3906HZ
//#define TIMER4_31250HZ

#if defined(TIMER4_30HZ)
  #define PRESCALER_TIMER4_1_2  1024
#endif
#if defined(TIMER4_122HZ)
  #define PRESCALER_TIMER4_1_2  256
#endif
#if defined(TIMER4_488HZ_DEFAULT)
  #define PRESCALER_TIMER4_1_2  64
#endif
#if defined(TIMER4_3906HZ)
  #define PRESCALER_TIMER4_1_2  8
#endif
#if defined(TIMER4_31250HZ)
  #define PRESCALER_TIMER4_1_2  1
#endif

//*********************************************************************************************************************
// Set PWM prescaler
//*********************************************************************************************************************
void set_PWM_prescaler(uint8_t pin, uint16_t prescale)
{
  byte mode;
  
  if (pin == 0 || pin == 1 || pin == 2 || pin == 5 || pin == 6 || pin == 9 || pin == 10)
  {
    switch (prescale) // 8-bit Timer/Counter 0, 16-bit Timer/Counter 1, ATmega328PB 16-bit Timer/Counter 3, ATmega328PB 16-bit Timer/Counter 4
    {
      case    1: mode = 0b001; break;
      case    8: mode = 0b010; break;
      case   64: mode = 0b011; break;
      case  256: mode = 0b100; break;
      case 1024: mode = 0b101; break;
      default: return;
    }
  }
  else if (pin == 3 || pin == 11)
  {
    switch (prescale) // 8-bit Timer/Counter 2
    {
      case    1: mode = 0b001; break;
      case    8: mode = 0b010; break;
      case   32: mode = 0b011; break;
      case   64: mode = 0b100; break;
      case  128: mode = 0b101; break;
      case  256: mode = 0b110; break;
      case 1024: mode = 0b111; break;
      default: return;
    }
  }
  
  if (pin == 5 || pin == 6) // 8-bit Timer/Counter 0, PD5(5), PD6(6)
  {
    TCCR0B = (TCCR0B & 0b11111000) | mode;
  }
  else if (pin == 9 || pin == 10) // 16-bit Timer/Counter 1, PB1(9), PB2(10)
  {
    TCCR1B = (TCCR1B & 0b11111000) | mode;
  }
  else if (pin == 3 || pin == 11) // 8-bit Timer/Counter 2, PD3(3), PB3(11)
  {
    TCCR2B = (TCCR2B & 0b11111000) | mode;
  }
#ifdef __AVR_ATmega328PB__
  else if (pin == 0 || pin == 2) // ATmega328PB 16-bit Timer/Counter 3, PD0(0)RX and specific pin PD2(2) is not paired
  {
    TCCR3B = (TCCR3B & 0b11111000) | mode;
  }
  else if (pin == 1 || pin == 2) // ATmega328PB 16-bit Timer/Counter 4, PD1(1)TX and specific pin PD2(2)
  {
    TCCR4B = (TCCR4B & 0b11111000) | mode;
  }
#endif
}

#endif // End __PWM_h__
 
