#ifndef FAILSAFE_H
#define FAILSAFE_H

#include <Arduino.h>
#include "pins.h"

bool emergencyStop = false;

void checkFailsafe() {
    if (digitalRead(EMERGENCY_STOP_PIN) == LOW) {
        emergencyStop = true;
    }
}

void stopMotors() {
    analogWrite(RPWM, 0);
    analogWrite(LPWM, 0);
    analogWrite(WPWM, 0);
}

#endif
