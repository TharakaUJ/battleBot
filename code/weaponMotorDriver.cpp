#include <Arduino.h>
#include "weaponMotorDriver.h"
#include "pins.h"

void softStart(int targetSpeed, int stepDelay)
{
    int speed = 0;
    while (speed < targetSpeed)
    {
        speed += 5; // Increase speed in small steps
        if (speed > targetSpeed)
            speed = targetSpeed; // Limit to max speed
        analogWrite(WRPWM, speed);
        analogWrite(WLPWM, 0); // Forward motion, adjust as needed
        delay(stepDelay);
    }
}

void weaponInit()
{
    // Initialize the weapon motor driver
    Serial.println("Initializing weapon motor driver...");

    pinMode(WRPWM, OUTPUT);
    pinMode(WLPWM, OUTPUT);
    pinMode(WEN, OUTPUT);

    digitalWrite(WEN, HIGH); // Enable the motor driver
}

void weaponSpinUp()
{
    // Spin up the weapon motor
    Serial.println("Spinning up weapon motor...");

    softStart(255, 10); // Spin up to full speed
}