
#ifndef __LED_h__
#define __LED_h__

#include <Arduino.h>
#include <stdint.h>

//*********************************************************************************************************************
// LED blink function
//*********************************************************************************************************************
uint32_t led_time = 0;
bool led_state = 0;

void blink(const uint8_t pin, uint16_t interval)
{
  if (millis() - led_time > interval)
  {
    led_time = millis();
    
    led_state = !led_state;
    
    digitalWrite(pin, led_state);
  }
}

#endif // End __LED_h__
 
