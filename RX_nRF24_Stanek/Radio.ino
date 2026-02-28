
//*********************************************************************************************************************
// Radio setup
//*********************************************************************************************************************
RF24 radio(PIN_CE, PIN_CSN); // Class driver

const byte retry_delay = (rc_channels * 3) / 7;

void radio_setup()
{
  radio.begin();
  radio.setAutoAck(1);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.setRetries(retry_delay, 0);
  radio.setChannel(RF_CHANNEL);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN); // RF24_PA_MIN (-18dBm), RF24_PA_LOW (-12dBm), RF24_PA_HIGH (-6dbm), RF24_PA_MAX (0dBm)
  radio.openReadingPipe(1, RF_address);
  radio.startListening();
}

//*********************************************************************************************************************
// Send and receive data
//*********************************************************************************************************************
unsigned int packet_counter = 0;
unsigned long packet_time = 0;
unsigned long rf_timeout = 0;

void send_and_receive_data()
{
  if (radio.available())
  {
    radio.read(&rc_packet, rc_packet_size);
    
    radio.writeAckPayload(1, &telemetry_packet, sizeof(telemetry_packet_size));
    
    packet_counter++;
    
    rf_timeout = millis();
  }
  
  if (millis() - packet_time > 1000)
  {
    packet_time = millis();
    telemetry_packet.rssi = map(packet_counter, 283, 294, 0, 100);
    telemetry_packet.rssi = constrain(telemetry_packet.rssi, 0, 100);
    //Serial.println(packet_counter);
    packet_counter = 0;
  }
  
  // If we lose RF data for 1 second, the LED blink at 0.1s interval
  if (millis() - rf_timeout > 1000)
  {
    load_fail_safe();
    
    blink(PIN_LED, 100);
  }
  else if (low_batt) // If the battery is low, the LED blink at 0.3s interval
  {
    blink(PIN_LED, 300);
  }
  else
  {
    digitalWrite(PIN_LED, HIGH); // Normal mode, LED is lit
  }
}
 
