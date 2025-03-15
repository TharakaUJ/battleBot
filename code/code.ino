#include "pins.h"
#include "receiver.h"
#include "motor_control.h"
#include "failsafe.h"
#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    // pinMode(EMERGENCY_STOP_PIN, INPUT_PULLUP);
 
    // setupMotors();
    setupReceiver();
}

void loop() {
    // checkFailsafe();

    updatePWMValues();

    Serial.print("Throttle: "); Serial.print(throttlePWM);
    Serial.print("\tSteering: "); Serial.print(steeringPWM);
    Serial.print("\tWeapon: "); Serial.println(weaponPWM);

    // if (emergencyStop) {
    //     stopMotors();
    //     Serial.println("Emergency Stop Activated!");
    //     return;
    // }

    // Map PWM signals to velocity values
    // int forwardVelocity = map(throttlePWM, 1000, 2000, -255, 255);
    // int turnVelocity = map(steeringPWM, 1000, 2000, -255, 255);
    // int weaponSpeed = map(weaponPWM, 1000, 2000, 0, 255);

    // controlMotors(forwardVelocity, turnVelocity, weaponSpeed);

    // Serial.print("Forward: "); Serial.print(forwardVelocity);
    // Serial.print("\tTurn: "); Serial.print(turnVelocity);
    // Serial.print("\tWeapon: "); Serial.println(weaponSpeed);

    delay(50);
}
