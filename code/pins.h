#ifndef PINS_H
#define PINS_H

// pwm pins
// 3, 5, 6, 9, 10, and 11

// Receiver Input Pins
#define CH1_PIN 16 // Throttle (Wheels)
#define CH2_PIN 17 // Steering (Wheels)
#define CH3_PIN 18 // Weapon Control

// BTS7960 Motor Driver Pins (Wheels) (Right)
#define RRPWM 6
#define RLPWM 23
#define RREN 7
#define RLEN 8

// BTS7960 Motor Driver Pins (Wheels) (Left)
#define LRPWM 9
#define LLPWM 22
#define LREN 12
#define LLEN 13

// Weapon Motor Pins
#define WPWM 10
#define WEN 14

// Emergency Stop Button
#define EMERGENCY_STOP_PIN 11

#endif
