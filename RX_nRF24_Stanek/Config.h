
#ifndef __Config__
#define __Config__

#include <Arduino.h>

/*
  *****************************************************************************************************************************************
  RC receiver configuration manual. See examples below "Custom configuration"
  *****************************************************************************************************************************************
  Setting a unique address (5 bytes number or character). It is hardcoded into the firmware of RC transmitter openAVRc and Multiprotocol TX
  const byte address[6] = "jirka";
  
  RF communication channel setting. It is hardcoded into the firmware of RC transmitter openAVRc and Multiprotocol TX
  RF_CHANNEL  0 to 125 (2.4GHz to 2.525GHz)
  
  Setting the maximum nominal battery voltage
  BATTERY_VOLTAGE  4.2
  
  Setting the minimum battery voltage for alarm
  MONITORED_VOLTAGE  < 4.2
  
  Servo and motor output selection
  SERVO_12CH             Separate servo outputs (2 to 12 servo channels)
  MOTOR1_2               Output for motor 1 and 2
  MIX_TANK_MOTOR1_2      Mixed "tank-arcade" output for motor 1 and 2
  SERVO_12CH_MOTOR1      Servos and motor 1 output (1 to 12 servo channels)
  SERVO_10CH_MOTOR1_2PB  ATmega328PB only! Servos, motor 1 and motor 2 output (1 to 10 servo channels)
  
  Setting the number of servo channels
  SERVO_CHANNELS  1 to 12
  
  Setting the PWM prescaler according to the requirements and limitations of the timers/counters. Details in the "PWM" file
  30HZ to 62500HZ
  
  Setting the motor reaction point. Prevents initial rotor magnetic resistance
  REACTION_MOTOR1, REACTION_MOTOR2  0 to 255
  
  Setting the maximum motor power. Suitable for RC transmitters without endpoint setting
  MAX_FORWARD_MOTOR1, MAX_REVERSE_MOTOR1, MAX_FORWARD_MOTOR2, MAX_REVERSE_MOTOR2  0 to 255
  
  Brake setting, no brake 0, maximum brake 255
  BRAKE_MOTOR1, BRAKE_MOTOR2  0 to 255
  
  Pin settings specific to my PCB.
  PIN_LED
*/

//*********************************************************************************************************************
// Custom configuration for a specific RC model
//*********************************************************************************************************************
//#define SERVO_12CH            // Glider Let L-13 Blanik 4ch
#define MOTOR1_2              // Buggy 1:32 2ch
//#define MIX_TANK_MOTOR1_2     // Eachine Monster 2ch
//#define SERVO_12CH_MOTOR1     // Ferari F-40 2ch
//#define SERVO_10CH_MOTOR1_2PB // Tank T-34/85 3ch

//********************************
// Glider Let L-13 Blanik 4ch
//********************************
#if defined(SERVO_12CH)
  const byte address[6] = "jirka";
  #define RF_CHANNEL  76
  #define BATTERY_VOLTAGE  4.2
  #define MONITORED_VOLTAGE  3.45
  #define SERVO_CHANNELS  4
#endif

//********************************
// Buggy 1:32 2ch
//********************************
#if defined(MOTOR1_2)
  const byte address[6] = "jirka";
  #define RF_CHANNEL  76
  #define PIN_LED  2
  #define BATTERY_VOLTAGE  4.2
  #define MONITORED_VOLTAGE  3.45
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
  const byte address[6] = "jirka";
  #define RF_CHANNEL  76
  #define BATTERY_VOLTAGE  4.2
  #define MONITORED_VOLTAGE  3.45
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
  const byte address[6] = "jirka";
  #define RF_CHANNEL  76
  #define BATTERY_VOLTAGE  4.2
  #define MONITORED_VOLTAGE  3.45
  #define SERVO_CHANNELS  1
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
  const byte address[6] = "jirka";
  #define RF_CHANNEL  76
  #define BATTERY_VOLTAGE  4.2
  #define MONITORED_VOLTAGE  3.45
  #define SERVO_CHANNELS  1
  // Motor 1
  #define TIMER2_122HZ
  #define REACTION_MOTOR1  0
  #define MAX_FORWARD_MOTOR1  255
  #define MAX_REVERSE_MOTOR1  255
  #define BRAKE_MOTOR1  0
  // Motor 2 ATmega328PB
  #define TIMER4_122HZ
  #define REACTION_MOTOR2  0
  #define MAX_FORWARD_MOTOR2  255
  #define MAX_REVERSE_MOTOR2  255
  #define BRAKE_MOTOR2  0
#endif

//*********************************************************************************************************************
// Number of RC motor channels
//*********************************************************************************************************************
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
  #define MOTOR1
#endif

#if defined(SERVO_10CH_MOTOR1_2PB)
  #define MOTOR_CHANNELS  2
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
// Radio data config (max. 32 bytes)
//*********************************************************************************************************************
// Received data array
const byte rc_channels = SERVO_CHANNELS + MOTOR_CHANNELS;

unsigned int rc_packet[rc_channels] = {1500};

// For one control channel with a value of 1000 to 2000 we need 2 bytes(packets)
const byte rc_packet_size = rc_channels * 2;

// Structure of sent ACK data
struct telemetry_packet_size
{
  byte rssi;
  byte batt_A1 = 255;
  byte batt_A2; // Not used yet
};
telemetry_packet_size telemetry_packet;

unsigned long rf_timeout = 0;

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

#endif // End __Config__
 
