
//*********************************************************************************************************************
// Load the fail-safe values
//*********************************************************************************************************************
void load_fail_safe()
{
  for (uint8_t i = MOTOR_CHANNELS; i < rc_channels; i++) // Does not read motor channels
  {
    EEPROM.get(i * 2, rx_packet.rc_data[i]);
    
    // If the stored RC channel values ​​are out of range, load the mid value
    if (rx_packet.rc_data[i] < MIN_CONTROL_VAL || rx_packet.rc_data[i] > MAX_CONTROL_VAL)
    {
      rx_packet.rc_data[i] = MID_CONTROL_VAL;
    }
  }
  
  // Safely setting the motor channels to the mid value
#if defined(MOTOR1_2) || defined(MIX_TANK_MOTOR1_2) || defined(SERVO_12CH_MOTOR1) || defined(SERVO_10CH_MOTOR1_2PB)
  for (uint8_t i = 0; i < MOTOR_CHANNELS; i++)
  {
    rx_packet.rc_data[i] = MID_CONTROL_VAL;
  }
#endif
}

//*********************************************************************************************************************
// Save fail-safe values. Button debounce treatment against multiple writes to EEPROM
//*********************************************************************************************************************
bool lastButtonState = 1;

void save_fail_safe()
{
  bool currentButtonState = digitalRead(PIN_FAIL_SAFE);
  
  if ((currentButtonState == LOW && lastButtonState == HIGH) || rx_packet.fail_safe_flag)
  {
    for (uint8_t i = MOTOR_CHANNELS; i < rc_channels; i++) // Does not save motor channels
    {
      EEPROM.put(i * 2, rx_packet.rc_data[i]);
    }
    
    rx_packet.fail_safe_flag = 0;
  }
  
  lastButtonState = currentButtonState;
}
 
