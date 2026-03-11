
//*********************************************************************************************************************
// Radio setup
//*********************************************************************************************************************
RF24 radio(PIN_CE, PIN_CSN); // Class driver

void radio_setup()
{
  radio.begin();
  radio.setAutoAck(1);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.setRetries(0, 0);
  radio.setChannel(RF_CHANNEL);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN); // RF24_PA_MIN (-18dBm), RF24_PA_LOW (-12dBm), RF24_PA_HIGH (-6dbm), RF24_PA_MAX (0dBm)
  radio.openReadingPipe(1, RF_address);
  radio.startListening();
}

//*********************************************************************************************************************
// Send and receive data
//*********************************************************************************************************************
uint16_t packet_counter = 0;
uint32_t packet_time = 0;
uint32_t rf_timeout = 0;

void send_and_receive_data()
{
  if (radio.available())
  {
    radio.writeAckPayload(1, &telemetry_packet, sizeof(telemetry_packet));
    
    radio.read(&rx_packet, radio.getDynamicPayloadSize());
    
    packet_counter++;
    
    rf_timeout = millis();
  }
  
  if (millis() - packet_time > 1000)
  {
    packet_time = millis();
    telemetry_packet.rssi = map(packet_counter, 322, 333, 0, 100);
    telemetry_packet.rssi = constrain(telemetry_packet.rssi, 0, 100);
    //Serial.println(packet_counter);
    packet_counter = 0;
  }
  
  if (millis() - rf_timeout > 1000) // If we lose RF data for 1 second, Fail-safe loaded and the LED blink at 0.1s interval
  {
    load_fail_safe();
    
    blink(PIN_LED, 100);
  }
  else if (low_batt) // If the battery is low, the LED blink at 0.3s interval
  {
    blink(PIN_LED, 300);
  }
  else if (fail_safe_led) // If you are saving fail-safe, the LED blink at 0.5s interval
  {
    blink(PIN_LED, 500);
  }
  else
  {
    digitalWrite(PIN_LED, HIGH); // Normal mode, LED is lit
  }
}
 
