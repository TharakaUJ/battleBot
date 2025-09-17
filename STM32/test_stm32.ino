/*
 * STM32 BluePill Test Sketch
 * Tests basic functionality before running the main battle bot code
 */

#include "pins.h"

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    // Test LED
    pinMode(LED_PIN, OUTPUT);
    
    // Test motor pins
    pinMode(RRPWM, OUTPUT);
    pinMode(RLPWM, OUTPUT);
    pinMode(LRPWM, OUTPUT);
    pinMode(LLPWM, OUTPUT);
    pinMode(REN, OUTPUT);
    pinMode(LEN, OUTPUT);
    pinMode(WRPWM, OUTPUT);
    pinMode(WLPWM, OUTPUT);
    pinMode(WEN, OUTPUT);
    
    Serial.println("STM32 BluePill Test Started!");
    Serial.println("LED should be blinking...");
}

void loop() {
    // Blink LED
    digitalWrite(LED_PIN, LOW);  // LED on (active low)
    delay(500);
    digitalWrite(LED_PIN, HIGH); // LED off
    delay(500);
    
    // Test motor pins with low PWM
    Serial.println("Testing motor pins...");
    
    // Enable motors
    digitalWrite(REN, HIGH);
    digitalWrite(LEN, HIGH);
    digitalWrite(WEN, HIGH);
    
    // Test each motor briefly at low speed
    analogWrite(RRPWM, 50);
    delay(200);
    analogWrite(RRPWM, 0);
    
    analogWrite(LRPWM, 50);
    delay(200);
    analogWrite(LRPWM, 0);
    
    analogWrite(WRPWM, 50);
    delay(200);
    analogWrite(WRPWM, 0);
    
    Serial.println("Test cycle complete");
    delay(2000);
}
