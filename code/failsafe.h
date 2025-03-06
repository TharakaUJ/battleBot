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
    analogWrite(RRPWM, 0);
    analogWrite(RLPWM, 0);
    analogWrite(LRPWM, 0);
    analogWrite(LLPWM, 0);
    analogWrite(WPWM, 0);
}

#endif
