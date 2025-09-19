#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include "pins.h"

// For ESP32, we need to set up the PWM channels
#define RIGHT_MOTOR_CHANNEL 0
#define LEFT_MOTOR_CHANNEL 1
#define WEAPON_ESC_CHANNEL 2  // PWM channel for weapon ESC

#define PWM_FREQ 50           // 50Hz for ESC (standard servo frequency)
#define PWM_RESOLUTION 16      // 16-bit resolution for smoother control
#define MAX_DUTY 65535        // 2^16 - 1

void setupMotors();
void controlMotors(int throttle, int steering);
void controlWeapon(int value);  // -255 to +255 range


// ESP32 uses ledc for PWM
void setupMotors() {
    // Configure wheel motor pins
    pinMode(RRPWM, OUTPUT);
    pinMode(RLPWM, OUTPUT);
    pinMode(REN, OUTPUT);
    
    pinMode(LRPWM, OUTPUT);
    pinMode(LLPWM, OUTPUT);
    pinMode(LEN, OUTPUT);
    
    // Enable motor drivers
    digitalWrite(REN, HIGH);
    digitalWrite(LEN, HIGH);
    
    // Configure weapon ESC PWM channel
    ledcSetup(WEAPON_ESC_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(WEAPON_ESC_PIN, WEAPON_ESC_CHANNEL);
    
    // Initialize weapon ESC - send neutral signal
    ledcWrite(WEAPON_ESC_CHANNEL, map(ESC_MID_PULSE, 0, 20000, 0, MAX_DUTY));
    
    // Wheel motors setup for PWM
    ledcSetup(RIGHT_MOTOR_CHANNEL, 5000, 8);  // 5kHz, 8-bit
    ledcSetup(LEFT_MOTOR_CHANNEL, 5000, 8);   // 5kHz, 8-bit
    
    ledcAttachPin(RRPWM, RIGHT_MOTOR_CHANNEL);
    ledcAttachPin(LRPWM, LEFT_MOTOR_CHANNEL);
    
    // Initially stop all motors
    controlMotors(0, 0);
    controlWeapon(0);
}

void controlMotors(int throttle, int steering) {
    // Calculate left and right motor speeds
    int leftMotor = throttle - steering;
    int rightMotor = throttle + steering;
    
    // Constrain to valid range
    leftMotor = constrain(leftMotor, -255, 255);
    rightMotor = constrain(rightMotor, -255, 255);
    
    // Control left motor
    if (leftMotor > 0) {
        ledcWrite(LEFT_MOTOR_CHANNEL, leftMotor);
        digitalWrite(LLPWM, LOW);
    } else if (leftMotor < 0) {
        ledcWrite(LEFT_MOTOR_CHANNEL, 0);
        digitalWrite(LLPWM, HIGH);
        ledcWrite(LEFT_MOTOR_CHANNEL, -leftMotor);
    } else {
        ledcWrite(LEFT_MOTOR_CHANNEL, 0);
        digitalWrite(LLPWM, LOW);
    }
    
    // Control right motor
    if (rightMotor > 0) {
        ledcWrite(RIGHT_MOTOR_CHANNEL, rightMotor);
        digitalWrite(RLPWM, LOW);
    } else if (rightMotor < 0) {
        ledcWrite(RIGHT_MOTOR_CHANNEL, 0);
        digitalWrite(RLPWM, HIGH);
        ledcWrite(RIGHT_MOTOR_CHANNEL, -rightMotor);
    } else {
        ledcWrite(RIGHT_MOTOR_CHANNEL, 0);
        digitalWrite(RLPWM, LOW);
    }
}

// Control weapon ESC (-255 to +255 range)
void controlWeapon(int value) {
    // Map from -255 to +255 range to ESC pulse width
    int pulseWidth;
    
    if (value == 0) {
        // Zero = neutral position
        pulseWidth = ESC_MID_PULSE;
    } else if (value > 0) {
        // Positive = forward (map 0-255 to mid-max)
        pulseWidth = map(value, 0, 255, ESC_MID_PULSE, ESC_MAX_PULSE);
    } else {
        // Negative = reverse (map -255-0 to min-mid)
        pulseWidth = map(value, -255, 0, ESC_MIN_PULSE, ESC_MID_PULSE);
    }
    
    // Convert microseconds to duty cycle
    uint32_t duty = map(pulseWidth, 0, 20000, 0, MAX_DUTY);
    
    // Write to ESC
    ledcWrite(WEAPON_ESC_CHANNEL, duty);
}


#endif