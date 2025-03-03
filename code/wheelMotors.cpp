#include <Arduino.h>
#include "wheelMotors.h"

void wheelInit() {
    // Initialize the wheel motors
    Serial.println("Initializing wheel motors...");
}

void forward() {
    // Move the robot forward
    Serial.println("Moving forward...");
}

void backward() {
    // Move the robot backward
    Serial.println("Moving backward...");
}

void stop() {
    // Stop the robot
    Serial.println("Stopping...");
}

void turnLeft() {
    // Turn the robot left
    Serial.println("Turning left...");
}

void turnRight() {
    // Turn the robot right
    Serial.println("Turning right...");
}