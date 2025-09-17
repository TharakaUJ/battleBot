#ifndef PINS_H
#define PINS_H

// STM32 BluePill Pin Definitions
// Using pin numbers that correspond to STM32F103C8T6

// Receiver Input Pins
#define S_BUS_IN PA10  // Serial1 RX pin for SBUS

// BTS7960 Motor Driver Pins (Wheels) (Right)
#define RRPWM PA0     // PWM-capable pin
#define RLPWM PA1     // PWM-capable pin  
#define REN PA8       // Digital pin

// BTS7960 Motor Driver Pins (Wheels) (Left)
#define LRPWM PA2     // PWM-capable pin
#define LLPWM PA3     // PWM-capable pin
#define LEN PA9       // Digital pin

// Weapon Motor Pins
#define WLPWM PB0     // PWM-capable pin
#define WRPWM PB1     // PWM-capable pin
#define WEN PB10      // Digital pin

// Built-in LED for status indication
#define LED_PIN PC13  // Built-in LED on BluePill

#define NOISE_THRESHOLD 15    // Ignore small values < 15 in PWM

#define THROTTLE_CHANNEL 1
#define STEERING_CHANNEL 0
#define WEAPON_CHANNEL 2
#define KILL_SWITCH_CHANNEL 5 // Channel 6 (zero-based index)
#define WEAPON_STATE_CHANNEL 6 // Channel 7
#define STEERING_INVERT_CHANNEL 7 // Channel 8

#define TIMEOUT_MS 500        // Stop bot if no SBUS data received in 500ms

#endif
