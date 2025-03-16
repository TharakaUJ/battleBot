#include "pins.h"
#include "motor_control.h"
#include "failsafe.h"
#include <Arduino.h>
#include "sbus.h"


bfs::SbusRx sbus_rx(&Serial2, S_BUS_IN, -1, true);

bfs::SbusData data;

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
    // Check failsafe conditions
    // checkFailsafe();

    if (sbus_rx.Read())
    {
        /* Get SBUS data */
        data = sbus_rx.data();

        // Map SBUS values to motor control range
        int throttle = map(data.ch[1], 172, 1811, 255, -255);  // CH1: Throttle
        int steering = map(data.ch[0], 172, 1811, 255, -255);  // CH2: Steering
        int weapon = map(data.ch[2], 172, 1811, 0, 255);       // CH3: Weapon control

        /* Handle failsafe conditions */
        if (data.failsafe)
        {
            Serial.println("⚠️ FAILSAFE TRIGGERED! ⚠️");
            throttle = 0;
            steering = 0;
            weapon = 0;
        }

        if (data.lost_frame)
        {
            Serial.println("⚠️ FRAME LOST! ⚠️");
            // We don’t necessarily stop the bot on a lost frame, only if failsafe triggers
        }

        /* Send values to motor control */
        controlMotors(throttle, steering, weapon);

        /* Debug Output */
        Serial.print("Throttle: "); Serial.print(throttle);
        Serial.print("\tSteering: "); Serial.print(steering);
        Serial.print("\tWeapon: "); Serial.println(weapon);
    }
}
