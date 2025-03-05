#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>
#include "pins.h"

volatile int throttlePWM, steeringPWM, weaponPWM;
unsigned long ch1_start, ch2_start, ch3_start;

void ch1_ISR()
{
    if (digitalRead(CH1_PIN) == HIGH)
        ch1_start = micros();
    else
        throttlePWM = micros() - ch1_start;
}

void ch2_ISR()
{
    if (digitalRead(CH2_PIN) == HIGH)
        ch2_start = micros();
    else
        steeringPWM = micros() - ch2_start;
}

void ch3_ISR()
{
    if (digitalRead(CH3_PIN) == HIGH)
        ch3_start = micros();
    else
        weaponPWM = micros() - ch3_start;
}

void setupReceiver()
{
    pinMode(CH1_PIN, INPUT);
    pinMode(CH2_PIN, INPUT);
    pinMode(CH3_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(CH1_PIN), ch1_ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(CH2_PIN), ch2_ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(CH3_PIN), ch3_ISR, CHANGE);
}

#endif
