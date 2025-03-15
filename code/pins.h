#ifndef PINS_H
#define PINS_H

// Receiver Input Pins
#define CH1_PIN 16 // Throttle (Wheels)
#define CH2_PIN 17 // Steering (Wheels)
#define CH3_PIN 18 // Weapon Control

// BTS7960 Motor Driver Pins (Wheels) (Right)
#define RRPWM 25
#define RLPWM 23
#define RREN 32
#define RLEN 33

// BTS7960 Motor Driver Pins (Wheels) (Left)
#define LRPWM 26
#define LLPWM 22
#define LREN 12
#define LLEN 13

// Weapon Motor Pins
#define WPWM 27
#define WEN 14

// Emergency Stop Button
#define EMERGENCY_STOP_PIN 4

#endif
