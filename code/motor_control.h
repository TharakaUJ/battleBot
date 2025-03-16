#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include "pins.h"

void setupMotors() {
    pinMode(RRPWM, OUTPUT);
    pinMode(RLPWM, OUTPUT);
    pinMode(LRPWM, OUTPUT);
    pinMode(LLPWM, OUTPUT);
    pinMode(RREN, OUTPUT);
    pinMode(RLEN, OUTPUT);
    pinMode(LLEN, OUTPUT);
    pinMode(LREN, OUTPUT);
    pinMode(WPWM, OUTPUT);
    pinMode(WEN, OUTPUT);

    digitalWrite(RREN, HIGH); 
    digitalWrite(LLEN, HIGH);
    digitalWrite(WEN, HIGH);  
}

void softStart(int &currentSpeed, int targetSpeed) {
    while (currentSpeed < targetSpeed) {
        currentSpeed += 5;
        if (currentSpeed > targetSpeed) currentSpeed = targetSpeed;
        delay(20);
    }
}

void controlMotors(int forwardVelocity, int turnVelocity, int weaponSpeed) {
    int leftSpeed = forwardVelocity - turnVelocity;  // Adjust left wheel
    int rightSpeed = forwardVelocity + turnVelocity; // Adjust right wheel

    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);

    // Left wheel control
    if (leftSpeed > 0) {
        analogWrite(LLPWM, 0);
        analogWrite(LRPWM, leftSpeed);
    } else {
        analogWrite(LLPWM, -leftSpeed);
        analogWrite(LRPWM, 0);
    }

    // Right wheel control
    if (rightSpeed > 0) {
        analogWrite(RLPWM, 0);
        analogWrite(RLPWM, rightSpeed);
    } else {
        analogWrite(RLPWM, -rightSpeed);
        analogWrite(RRPWM, 0);
    }

    // Soft Start for Weapon Motor
    static int currentWeaponSpeed = 0;
    softStart(currentWeaponSpeed, weaponSpeed);
    analogWrite(WPWM, currentWeaponSpeed);
}

#endif
