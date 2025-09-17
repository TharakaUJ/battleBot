#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include "pins.h"

void setupMotors()
{
    // Set all motor control pins as outputs
    pinMode(RRPWM, OUTPUT);
    pinMode(RLPWM, OUTPUT);
    pinMode(LRPWM, OUTPUT);
    pinMode(LLPWM, OUTPUT);
    pinMode(REN, OUTPUT);
    pinMode(LEN, OUTPUT);
    pinMode(WRPWM, OUTPUT);
    pinMode(WLPWM, OUTPUT);
    pinMode(WEN, OUTPUT);
    
    // Set LED pin as output for status indication
    pinMode(LED_PIN, OUTPUT);

    // Enable motor drivers
    digitalWrite(REN, HIGH);
    digitalWrite(LEN, HIGH);
    digitalWrite(WEN, HIGH);
    
    // Turn on LED to indicate system is ready
    digitalWrite(LED_PIN, LOW); // LED is active low on BluePill
    
    Serial.println("Motors initialized for STM32 BluePill");
}

void controlMotors(int forwardVelocity, int turnVelocity)
{
    int leftSpeed = forwardVelocity - turnVelocity;  // Adjust left wheel
    int rightSpeed = forwardVelocity + turnVelocity; // Adjust right wheel

    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);

    // Left wheel control
    if (leftSpeed > 0)
    {
        analogWrite(LLPWM, 0);
        analogWrite(LRPWM, leftSpeed);
    }
    else
    {
        analogWrite(LLPWM, -leftSpeed);
        analogWrite(LRPWM, 0);
    }

    // Right wheel control
    if (rightSpeed > 0)
    {
        analogWrite(RLPWM, 0);
        analogWrite(RRPWM, rightSpeed);
    }
    else
    {
        analogWrite(RLPWM, -rightSpeed);
        analogWrite(RRPWM, 0);
    }
    
    // Blink LED when motors are active
    if (forwardVelocity != 0 || turnVelocity != 0) {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
}

void controlWeapon(int weaponVelocity)
{
    weaponVelocity = constrain(weaponVelocity, -255, 255);
    
    if (weaponVelocity > 0)
    {
        analogWrite(WLPWM, 0);
        analogWrite(WRPWM, weaponVelocity);
    }
    else if (weaponVelocity < 0)
    {
        analogWrite(WLPWM, -weaponVelocity);
        analogWrite(WRPWM, 0);
    }
    else
    {
        // Stop weapon motor
        analogWrite(WLPWM, 0);
        analogWrite(WRPWM, 0);
    }
}

#endif
