#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include "pins.h"

void setupMotors() {
    pinMode(RPWM, OUTPUT);
    pinMode(LPWM, OUTPUT);
    pinMode(REN, OUTPUT);
    pinMode(LEN, OUTPUT);
    pinMode(WPWM, OUTPUT);
    pinMode(WEN, OUTPUT);

    digitalWrite(REN, HIGH); 
    digitalWrite(LEN, HIGH);
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
        analogWrite(LPWM, 0);
        analogWrite(RPWM, leftSpeed);
    } else {
        analogWrite(LPWM, -leftSpeed);
        analogWrite(RPWM, 0);
    }

    // Right wheel control
    if (rightSpeed > 0) {
        analogWrite(LEN, 0);
        analogWrite(REN, rightSpeed);
    } else {
        analogWrite(LEN, -rightSpeed);
        analogWrite(REN, 0);
    }

    // Soft Start for Weapon Motor
    static int currentWeaponSpeed = 0;
    softStart(currentWeaponSpeed, weaponSpeed);
    analogWrite(WPWM, currentWeaponSpeed);
}

#endif
