#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>
#include "pins.h"

volatile int throttlePWM = 1500, steeringPWM = 1500, weaponPWM = 1500;

void updatePWMValues() {
    throttlePWM = pulseIn(CH1_PIN, HIGH, 25000); // Max timeout 25ms (failsafe)
    steeringPWM = pulseIn(CH2_PIN, HIGH, 25000);
    weaponPWM = pulseIn(CH3_PIN, HIGH, 25000);

    // Failsafe: If no valid pulse is received, reset to neutral
    if (throttlePWM == 0) throttlePWM = 1500;
    if (steeringPWM == 0) steeringPWM = 1500;
    if (weaponPWM == 0) weaponPWM = 1500;
}

void setupReceiver() {
    pinMode(CH1_PIN, INPUT);
    pinMode(CH2_PIN, INPUT);
    pinMode(CH3_PIN, INPUT);
}

#endif
