#include "pins.h"
#include "motor_control.h"
#include <Arduino.h>
#include "sbus.h"

bfs::SbusRx sbus_rx(&Serial2, S_BUS_IN, -1, true);
bfs::SbusData data;

unsigned long lastSignalTime = 0; // Tracks last valid SBUS data

void setup()
{
    Serial.begin(115200);

    /* Start SBUS communication */
    sbus_rx.Begin();
    Serial.println("SBUS Receiver Started!");

    /* Initialize motors */
    setupMotors();
}

void loop()
{
    if (sbus_rx.Read())
    {
        /* Get SBUS data */
        data = sbus_rx.data();
        lastSignalTime = millis();  // Update last valid signal time

        // Map SBUS values to motor control range
        int throttle = map(data.ch[THROTTLE_CHANNEL], 172, 1811, 255, -255);  // CH1: Throttle
        int steering = map(data.ch[STEERING_CHANNEL], 172, 1811, 255, -255);  // CH2: Steering
        int weapon = map(data.ch[WEAPON_CHANNEL], 172, 1811, 0, 255);       // CH3: Weapon control
        bool killSwitch = (data.ch[KILL_SWITCH_CHANNEL] > 1000); // CH6: Kill switch

        /* Noise Filtering */
        if (abs(throttle) < NOISE_THRESHOLD) throttle = 0;
        if (abs(steering) < NOISE_THRESHOLD) steering = 0;
        if (weapon < NOISE_THRESHOLD) weapon = 0;

        /* Handle failsafe conditions */
        if (data.failsafe || killSwitch)
        {
            Serial.println("⚠️ EMERGENCY STOP! FAILSAFE or KILL SWITCH ACTIVE! ⚠️");
            throttle = 0;
            steering = 0;
            weapon = 0;
        }

        if (data.lost_frame)
        {
            Serial.println("⚠️ FRAME LOST! ⚠️");
        }

        /* Send values to motor control */
        controlMotors(throttle, steering, weapon);

        /* Debug Output */
        Serial.print("Throttle: "); Serial.print(throttle);
        Serial.print("\tSteering: "); Serial.print(steering);
        Serial.print("\tWeapon: "); Serial.print(weapon);
        Serial.print("\tKill Switch: "); Serial.println(killSwitch ? "ON" : "OFF");
    }

    /* No Signal Timeout - If no SBUS data received in TIMEOUT_MS, stop the bot */
    if (millis() - lastSignalTime > TIMEOUT_MS)
    {
        Serial.println("⛔ NO SIGNAL! STOPPING BOT ⛔");
        controlMotors(0, 0, 0);  // Stop all motors
    }
}
