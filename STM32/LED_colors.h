#ifndef LED_COLORS_H
#define LED_COLORS_H

#include "pins.h"
#include <Arduino.h>

// RGB Color Definitions (0-255 values)
struct RGBColor {
    int red;
    int green;
    int blue;
};

// Status Colors
const RGBColor COLOR_OFF =        {0,   0,   0};    // Off
const RGBColor COLOR_READY =      {0,   255, 0};    // Green - System Ready
const RGBColor COLOR_ARMED =      {255, 255, 0};    // Yellow - Weapon Armed
const RGBColor COLOR_EMERGENCY =  {255, 0,   0};    // Red - Emergency Stop/Failsafe
const RGBColor COLOR_NO_SIGNAL =  {255, 0,   255};  // Magenta - SBUS Lost/No Signal
const RGBColor COLOR_FRAME_LOST = {0,   0,   255};  // Blue - Frame Lost
const RGBColor COLOR_KILL_SWITCH ={255, 128, 0};    // Orange - Kill Switch Active
const RGBColor COLOR_INITIALIZING={128, 0,   128};  // Purple - System Initializing
const RGBColor COLOR_LOW_BATTERY ={255, 255, 255};  // White - Low Battery (if needed)

// LED Control Functions
void setupRGBLED();
void setRGBColor(RGBColor color);
void setRGBColor(int red, int green, int blue);
void ledBlink(RGBColor color, int duration_ms);
void ledPulse(RGBColor color);

// Status LED Functions
void ledReady();
void ledArmed();
void ledEmergency();
void ledNoSignal();
void ledFrameLost();
void ledKillSwitch();
void ledInitializing();
void ledOff();

// Initialize RGB LED pins
void setupRGBLED() {
    pinMode(RGB_RED_PIN, OUTPUT);
    pinMode(RGB_GREEN_PIN, OUTPUT);
    pinMode(RGB_BLUE_PIN, OUTPUT);
    
    // Start with LED off
    ledOff();
}

// Set RGB color using struct
void setRGBColor(RGBColor color) {
    analogWrite(RGB_RED_PIN, color.red);
    analogWrite(RGB_GREEN_PIN, color.green);
    analogWrite(RGB_BLUE_PIN, color.blue);
}

// Set RGB color using individual values
void setRGBColor(int red, int green, int blue) {
    analogWrite(RGB_RED_PIN, red);
    analogWrite(RGB_GREEN_PIN, green);
    analogWrite(RGB_BLUE_PIN, blue);
}

// Blink LED with specific color
void ledBlink(RGBColor color, int duration_ms) {
    setRGBColor(color);
    delay(duration_ms);
    ledOff();
    delay(duration_ms);
}

// Pulse effect (future enhancement)
void ledPulse(RGBColor color) {
    // Could implement PWM pulsing effect here
    setRGBColor(color);
}

// Status LED Functions
void ledReady() {
    setRGBColor(COLOR_READY);  // Green
}

void ledArmed() {
    setRGBColor(COLOR_ARMED);  // Yellow
}

void ledEmergency() {
    setRGBColor(COLOR_EMERGENCY);  // Red
}

void ledNoSignal() {
    setRGBColor(COLOR_NO_SIGNAL);  // Magenta
}

void ledFrameLost() {
    setRGBColor(COLOR_FRAME_LOST);  // Blue
}

void ledKillSwitch() {
    setRGBColor(COLOR_KILL_SWITCH);  // Orange
}

void ledInitializing() {
    setRGBColor(COLOR_INITIALIZING);  // Purple
}

void ledOff() {
    setRGBColor(COLOR_OFF);  // Off
}


#endif