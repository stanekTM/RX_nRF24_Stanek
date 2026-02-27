
//*********************************************************************************************************************
// If the stored RC channel values ​​are out of range, load the mean value, otherwise load the fail-safe values
//*********************************************************************************************************************
void load_fail_safe()
{
  for (byte i = MOTOR_CHANNELS; i < rc_channels; i++) // Does not read motor channels
  {
    if (EEPROM.get(i * 2, rc_packet[i]) < MIN_CONTROL_VAL || EEPROM.get(i * 2, rc_packet[i]) > MAX_CONTROL_VAL)
    {
      rc_packet[i] = MID_CONTROL_VAL;
    }
    else
    {
      EEPROM.get(i * 2, rc_packet[i]);
    }
  }

// Safe motor channels to neutral
#if defined(MOTOR1_2) || defined(MIX_TANK_MOTOR1_2) || defined(SERVO_12CH_MOTOR1) || defined(SERVO_10CH_MOTOR1_2PB)
  for (byte i = 0; i < MOTOR_CHANNELS; i++)
  {
    rc_packet[i] = MID_CONTROL_VAL;
  }
#endif 
  //Serial.println(rc_packet[0]);
}

//*********************************************************************************************************************
// Save fail-safe
//*********************************************************************************************************************
void save_fail_safe()
{
  for (byte i = MOTOR_CHANNELS; i < rc_channels; i++) // Does not read motor channels
  {
    if (digitalRead(PIN_FAIL_SAFE) == LOW)
    {
      EEPROM.put(i * 2, rc_packet[i]);
    }
  }
  
  while (digitalRead(PIN_FAIL_SAFE) == LOW)
  {
    blink(PIN_LED, 500);
  }
}
 
