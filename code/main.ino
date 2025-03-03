#include <Arduino.h>
#include "weaponMotorDriver.h"
#include "wheelMotors.h"

void setup() {
    // Initialize serial communication at 9600 bits per second
    Serial.begin(9600);
    wheelInit();
    weaponInit();
}

void loop() {
    // Print "Hello, World!" to the serial monitor
    Serial.println("Hello, World!");
    
    // Wait for a second
    delay(1000);
}