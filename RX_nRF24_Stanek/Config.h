
#ifndef __Config_h__
#define __Config_h__

#include <Arduino.h>
#include <stdint.h>

/*
  ***************************************************************************************************************************
  RC receiver configuration manual. See examples below "Custom configuration"
  ***************************************************************************************************************************
  Setting a unique address (5 bytes number or character).
  It is hardcoded into the firmware of RC transmitter OpenAVRc and my TX Multiprotocol Stanek
  - const uint8_t RF_address[6] = "jirka";
  
  RF channel setting.
  It is hardcoded into the firmware of RC transmitter OpenAVRc and my TX Multiprotocol Stanek
  - RF_CHANNEL  0 to 125 (2.4GHz to 2.525GHz)
  
  Setting the maximum nominal battery voltage
  - BATTERY_VOLTAGE  4.2
  
  Setting the minimum battery voltage for alarm
  - MONITORED_VOLTAGE  < 4.2
  
  Servo and motor output selection.
  The number of channels for servos and motors is determined by the number of RC channels of the transmitter (min. 2)
  - SERVO_12CH             Separate servo outputs (2 to 12 servo channels)
  - MOTOR1_2               Motor output 1 and 2
  - MIX_TANK_MOTOR1_2      "Tank-arcade" mix of motor 1 and 2
  - SERVO_12CH_MOTOR1      Motor 1 and servo output (1 to 12 servo channels)
  - SERVO_10CH_MOTOR1_2PB  ATmega328PB only! Motor 1 and 2 and servo output (0 to 10 servo channels)
  
  Setting the PWM prescaler according to the requirements and limitations of the timers/counters. Details in the "PWM.h" file
  - 30HZ to 62500HZ
  
  Setting the motor reaction point. Prevents initial rotor magnetic resistance
  - REACTION_MOTOR1, REACTION_MOTOR2  0 to 255
  
  Setting the maximum motor power. Suitable for RC transmitters without endpoint setting
  - MAX_FORWARD_MOTOR1, MAX_REVERSE_MOTOR1, MAX_FORWARD_MOTOR2, MAX_REVERSE_MOTOR2  0 to 255
  
  Brake setting, no brake 0, maximum brake 255
  - BRAKE_MOTOR1, BRAKE_MOTOR2  0 to 255
  
  Pin settings specific to my PCB https://github.com/stanekTM/RX_nRF24_Stanek/blob/master/documents/2micro_rx_layout.png
  - PIN_LED
  
  Setting fail-safe servo channels outside of motor channels (motor 1 and 2 fixed in neutral).
  The setting is done by connecting pin A5 to GND or from a Multiprotocol TX transmitter (later also OpenAVRc)
*/

//*********************************************************************************************************************
// Custom configuration for a specific RC model
//*********************************************************************************************************************
#define SERVO_12CH            // Glider Let L-13 Blanik 4ch
//#define MOTOR1_2              // Buggy 1:32 2ch
//#define MIX_TANK_MOTOR1_2     // Eachine Monster 2ch
//#define SERVO_12CH_MOTOR1     // Ferari F-40 2ch
//#define SERVO_10CH_MOTOR1_2PB // Tank T-34/85 3ch

//********************************
// Glider Let L-13 Blanik 4ch
//********************************
#if defined(SERVO_12CH)
  const uint8_t RF_address[6] = "jirka";
  #define RF_CHANNEL  76
  #define BATTERY_VOLTAGE  4.2
  #define MONITORED_VOLTAGE  3.45
#endif

//********************************
// Buggy 1:32 2ch
//********************************
#if defined(MOTOR1_2)
  const uint8_t RF_address[6] = "jirka";
  #define RF_CHANNEL  76
  #define BATTERY_VOLTAGE  4.2
  #define MONITORED_VOLTAGE  3.45
  #define PIN_LED  2
  // Motor 1
  #define TIMER2_488HZ_DEFAULT
  #define REACTION_MOTOR1  0
  #define MAX_FORWARD_MOTOR1  255
  #define MAX_REVERSE_MOTOR1  255
  #define BRAKE_MOTOR1  0
  // Motor 2
  #define TIMER1_488HZ_DEFAULT
  #define REACTION_MOTOR2  0
  #define MAX_FORWARD_MOTOR2  255
  #define MAX_REVERSE_MOTOR2  255
  #define BRAKE_MOTOR2  0
#endif

//********************************
// Eachine Monster 2ch
//********************************
#if defined(MIX_TANK_MOTOR1_2)
  const uint8_t RF_address[6] = "jirka";
  #define RF_CHANNEL  76
  #define BATTERY_VOLTAGE  4.2
  #define MONITORED_VOLTAGE  3.45
  #define PIN_LED  2
  // Motor 1
  #define TIMER2_122HZ
  #define REACTION_MOTOR1  0
  #define MAX_FORWARD_MOTOR1  255
  #define MAX_REVERSE_MOTOR1  255
  #define BRAKE_MOTOR1  255
  // Motor 2
  #define TIMER1_122HZ
  #define REACTION_MOTOR2  0
  #define MAX_FORWARD_MOTOR2  255
  #define MAX_REVERSE_MOTOR2  255
  #define BRAKE_MOTOR2  255
#endif

//********************************
// Ferari F-40 2ch
//********************************
#if defined(SERVO_12CH_MOTOR1)
  const uint8_t RF_address[6] = "jirka";
  #define RF_CHANNEL  76
  #define BATTERY_VOLTAGE  4.2
  #define MONITORED_VOLTAGE  3.45
  // Motor 1
  #define TIMER2_122HZ
  #define REACTION_MOTOR1  0
  #define MAX_FORWARD_MOTOR1  255
  #define MAX_REVERSE_MOTOR1  255
  #define BRAKE_MOTOR1  255
#endif

//********************************
// Tank T-34/85 3ch
//********************************
#if defined(SERVO_10CH_MOTOR1_2PB)
  const uint8_t RF_address[6] = "jirka";
  #define RF_CHANNEL  76
  #define BATTERY_VOLTAGE  4.2
  #define MONITORED_VOLTAGE  3.45
  // Motor 1
  #define TIMER2_122HZ
  #define REACTION_MOTOR1  0
  #define MAX_FORWARD_MOTOR1  255
  #define MAX_REVERSE_MOTOR1  255
  #define BRAKE_MOTOR1  255
  // Motor 2 ATmega328PB
  #define TIMER4_122HZ
  #define REACTION_MOTOR2  0
  #define MAX_FORWARD_MOTOR2  255
  #define MAX_REVERSE_MOTOR2  255
  #define BRAKE_MOTOR2  255
#endif

//*********************************************************************************************************************
// The number of channels for servos and motors is determined by the number of RC channels of the transmitter (min. 2)
//*********************************************************************************************************************
#if defined(SERVO_12CH)
  #define SERVO_CHANNELS  12
#endif

#if defined(MOTOR1_2)
  #define MOTOR_CHANNELS  2
  #define MOTOR1
  #define MOTOR2
#endif

#if defined(MIX_TANK_MOTOR1_2)
  #define MOTOR_CHANNELS  2
#endif

#if defined(SERVO_12CH_MOTOR1)
  #define MOTOR_CHANNELS  1
  #define SERVO_CHANNELS  12
  #define MOTOR1
#endif

#if defined(SERVO_10CH_MOTOR1_2PB)
  #define MOTOR_CHANNELS  2
  #define SERVO_CHANNELS  10
  #define MOTOR1
  #define MOTOR2PB
#endif

//*********************************************************************************************************************
// If there is no output to servos or motors, set RC channels to 0
//*********************************************************************************************************************
#ifndef SERVO_CHANNELS
  #define SERVO_CHANNELS  0
#endif

#ifndef MOTOR_CHANNELS
  #define MOTOR_CHANNELS  0
#endif

//*********************************************************************************************************************
// Config radio
//*********************************************************************************************************************
const uint8_t rc_channels = MOTOR_CHANNELS + SERVO_CHANNELS;

// Structure of received data (max. 32 bytes)
struct rx_packet
{
  bool fail_safe_flag = 0;
  uint16_t rc_data[rc_channels] = {1500};
}
rx_packet;

// Structure of sent ACK data
struct telemetry_packet
{
  uint8_t rssi;
  uint8_t batt_A1 = 255;
  uint8_t batt_A2; // Not used yet
}
telemetry_packet;

//*********************************************************************************************************************
// Dead zone adjustment of poor quality RC transmitter pots for motor control
//*********************************************************************************************************************
#define DEAD_ZONE  15

//*********************************************************************************************************************
// Setting the control range value
//*********************************************************************************************************************
#define MIN_CONTROL_VAL  1000
#define MID_CONTROL_VAL  1500
#define MAX_CONTROL_VAL  2000

#endif // End __Config_h__
 
