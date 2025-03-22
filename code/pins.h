#ifndef PINS_H
#define PINS_H

// Receiver Input Pins
#define S_BUS_IN 16

// BTS7960 Motor Driver Pins (Wheels) (Right)
#define RRPWM 25
#define RLPWM 26
#define RREN 34
#define RLEN 33

// BTS7960 Motor Driver Pins (Wheels) (Left)
#define LRPWM 19
#define LLPWM 18
#define LREN 21
#define LLEN 13

// Weapon Motor Pins
#define WPWM 27
#define WEN 14

#define NOISE_THRESHOLD 15    // Ignore small values < 15 in PWM

#define THROTTLE_CHANNEL 1
#define STEERING_CHANNEL 0
#define WEAPON_CHANNEL 2
#define KILL_SWITCH_CHANNEL 5 // Channel 6 (zero-based index)

#define TIMEOUT_MS 500        // Stop bot if no SBUS data received in 500ms

#endif
