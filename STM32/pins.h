#ifndef PINS_H
#define PINS_H

// STM32 BluePill Pin Definitions
// Using pin numbers that correspond to STM32F103C8T6

// Receiver Input Pins
#define S_BUS_IN PA10  // Serial1 RX pin for SBUS

// IBT_2 Motor Driver Pins (Left Motor) - JST near PB4-PB9
#define LRPWM PA1     // PWM-capable pin (Timer 4, Channel 1)
#define LLPWM PA0     // PWM-capable pin (Timer 4, Channel 2)
#define LEN PB5       // Digital pin (Enable)
#define LR_IS PB0     // Analog pin for right current sensing
#define LL_IS PB1     // Analog pin for left current sensing

// IBT_2 Motor Driver Pins (Right Motor) - JST near PA7-PC13
#define RRPWM PA6     // PWM-capable pin (Timer 3, Channel 2)
#define RLPWM PA7     // PWM-capable pin (Timer 3, Channel 3)
#define REN PA4       // Digital pin (Enable)
#define RR_IS PA3     // Analog pin for right current sensing
#define RL_IS PA2     // Analog pin for left current sensing

// Weapon Motor Pins (if still needed)
#define WLPWM PB6     // PWM-capable pin
#define WRPWM PB7     // PWM-capable pin
#define WEN PB8      // Digital pin

// Buzzer Pin
#define BUZZER_PIN PB12  // PWM-capable pin for buzzer/beeper

// Built-in LED for status indication
#define LED_PIN PC13  // Built-in LED on BluePill

#define RX PB11
#define TX PB10

#define NOISE_THRESHOLD 15    // Ignore small values < 15 in PWM

#define THROTTLE_CHANNEL 1
#define STEERING_CHANNEL 0
#define WEAPON_CHANNEL 2
#define KILL_SWITCH_CHANNEL 5 // Channel 6 (zero-based index)
#define WEAPON_STATE_CHANNEL 6 // Channel 7
#define STEERING_INVERT_CHANNEL 7 // Channel 8

#define TIMEOUT_MS 500        // Stop bot if no SBUS data received in 500ms

#endif
