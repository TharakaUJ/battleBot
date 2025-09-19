#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "pins.h"
#include <Servo.h> // Only needed for weapon ESC
#include <Arduino.h>

// Weapon ESC Control Object
extern Servo weaponESC;

// Motor Control Functions
void setupMotors();
void controlMotors(int throttle, int steering);
void controlWeapon(int weaponPower);
void stopAllMotors();

// IBT-2 Helper Functions (for drive motors)
void setMotorSpeed(int rpwmPin, int lpwmPin, int enablePin, int speed);

// ESC Helper Functions (for weapon motor)
int mapToESCPulse(int value);

// Weapon ESC Control Object
Servo weaponESC;

void setupMotors()
{
    // Setup IBT-2 pins for drive motors
    pinMode(LRPWM, OUTPUT);
    pinMode(LLPWM, OUTPUT);
    pinMode(LEN, OUTPUT);
    pinMode(RRPWM, OUTPUT);
    pinMode(RLPWM, OUTPUT);
    pinMode(REN, OUTPUT);

    // Enable IBT-2 drivers
    digitalWrite(LEN, HIGH);
    digitalWrite(REN, HIGH);

    // Setup weapon ESC
    weaponESC.attach(WEAPON_ESC_PIN);
    weaponESC.writeMicroseconds(ESC_NEUTRAL_PULSE); // Initialize to neutral

    // ESC arming delay
    delay(2000);

    Serial2.println("IBT-2 drivers and weapon ESC initialized");
}

// IBT-2 motor control function
void setMotorSpeed(int rpwmPin, int lpwmPin, int enablePin, int speed)
{
    // Ensure enable is high
    digitalWrite(enablePin, HIGH);

    if (speed > 0)
    {
        // Forward direction
        analogWrite(rpwmPin, speed);
        analogWrite(lpwmPin, 0);
    }
    else if (speed < 0)
    {
        // Reverse direction
        analogWrite(rpwmPin, 0);
        analogWrite(lpwmPin, -speed);
    }
    else
    {
        // Stop
        analogWrite(rpwmPin, 0);
        analogWrite(lpwmPin, 0);
    }
}

// Control drive motors with IBT-2 drivers
void controlMotors(int throttle, int steering)
{
    // Calculate left and right motor speeds for tank steering
    int leftSpeed = throttle + steering;
    int rightSpeed = throttle - steering;

    // Clamp to valid range
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);

    // Control IBT-2 drivers
    setMotorSpeed(LRPWM, LLPWM, LEN, leftSpeed);
    setMotorSpeed(RRPWM, RLPWM, REN, rightSpeed);
}

// Map -255 to +255 range to ESC pulse width
int mapToESCPulse(int value)
{
    // Clamp input value
    value = constrain(value, -255, 255);

    // Map to ESC pulse width
    return map(value, -255, 255, ESC_MIN_PULSE, ESC_MAX_PULSE);
}

// Control weapon motor with ESC
void controlWeapon(int weaponPower)
{
    // Clamp weapon power
    weaponPower = constrain(weaponPower, -255, 255);

    // Convert to ESC pulse width and send
    int pulseWidth = mapToESCPulse(weaponPower);
    weaponESC.writeMicroseconds(pulseWidth);
}

// Emergency stop - stop all motors
void stopAllMotors()
{
    // Stop IBT-2 drive motors
    setMotorSpeed(LRPWM, LLPWM, LEN, 0);
    setMotorSpeed(RRPWM, RLPWM, REN, 0);

    // Stop weapon ESC
    weaponESC.writeMicroseconds(ESC_NEUTRAL_PULSE);
}

#endif