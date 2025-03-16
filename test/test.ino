#include "sbus.h"

/* SBUS object for reading */
bfs::SbusRx sbus_rx(&Serial2, 16, 17, true);

/* SBUS data */
bfs::SbusData data;

void setup() {
    Serial.begin(115200);
    // while (!Serial.available()) {}  // Wait for Serial to start

    /* Start SBUS communication */
    sbus_rx.Begin();

    Serial.println("SBUS Receiver Started!");
}

void loop() {
    if (sbus_rx.Read()) {
        /* Get the SBUS data */
        data = sbus_rx.data();

        /* Read throttle, steering, and weapon from SBUS */
        int throttle = map(data.ch[0], 172, 1811, -255, 255);  // CH1: Throttle
        int steering = map(data.ch[1], 172, 1811, -255, 255);  // CH2: Steering
        int weapon = map(data.ch[2], 172, 1811, 0, 255);       // CH3: Weapon

        /* Display the values for debugging */
        Serial.print("Throttle: "); Serial.print(throttle);
        Serial.print(" | Steering: "); Serial.print(steering);
        Serial.print(" | Weapon: "); Serial.println(weapon);

        /* Check failsafe or lost frame */
        if (data.failsafe) {
            Serial.println("⚠️  FAILSAFE TRIGGERED!  ⚠️");
        }
        if (data.lost_frame) {
            Serial.println("⚠️  FRAME LOST!  ⚠️");
        }

        /* ADD MOTOR CONTROL CODE HERE */
    }
}
