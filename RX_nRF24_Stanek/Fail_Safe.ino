
//*********************************************************************************************************************
// If the stored RC channel values ​​are out of range, load the mid value, otherwise load the fail-safe values
//*********************************************************************************************************************
void load_fail_safe()
{
  for (uint8_t i = MOTOR_CHANNELS; i < rc_channels; i++) // Does not read motor channels
  {
    if (EEPROM.get(i * 2, rx_packet.rc_data[i]) < MIN_CONTROL_VAL || EEPROM.get(i * 2, rx_packet.rc_data[i]) > MAX_CONTROL_VAL)
    {
      rx_packet.rc_data[i] = MID_CONTROL_VAL;
    }
    else
    {
      EEPROM.get(i * 2, rx_packet.rc_data[i]);
    }
  }
  
// Safe motor channels to mid value
#if defined(MOTOR1_2) || defined(MIX_TANK_MOTOR1_2) || defined(SERVO_12CH_MOTOR1) || defined(SERVO_10CH_MOTOR1_2PB)
  for (uint8_t i = 0; i < MOTOR_CHANNELS; i++)
  {
    rx_packet.rc_data[i] = MID_CONTROL_VAL;
  }
#endif
}

//*********************************************************************************************************************
// Save fail-safe
//*********************************************************************************************************************
void save_fail_safe()
{
  if ((digitalRead(PIN_FAIL_SAFE) == LOW) || rx_packet.fail_safe_flag)
  {
    for (uint8_t i = MOTOR_CHANNELS; i < rc_channels; i++) // Does not save motor channels
    {
      EEPROM.put(i * 2, rx_packet.rc_data[i]);
    }
  }
}
 
