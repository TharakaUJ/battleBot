#ifndef BUZZER_CONTROL_H
#define BUZZER_CONTROL_H

#include "pins.h"
#include <Arduino.h>

// Buzzer tone frequencies (Hz)
#define TONE_READY 800       // Medium tone - System ready
#define TONE_ARMED 1200      // High tone - Weapon armed
#define TONE_EMERGENCY 300   // Low urgent tone - Emergency
#define TONE_KILL_SWITCH 400 // Low warning tone - Kill switch
#define TONE_NO_SIGNAL 600   // Medium warning - No signal
#define TONE_FRAME_LOST 900  // High warning - Frame lost
#define TONE_STARTUP 1000    // Startup beep

// Buzzer pattern durations (ms)
#define BEEP_SHORT 100
#define BEEP_MEDIUM 250
#define BEEP_LONG 500
#define BEEP_PAUSE 150

// Buzzer Control Functions
void setupBuzzer();
void buzzerTone(int frequency, int duration);
void buzzerOff();
void buzzerBeep(int frequency, int duration, int count = 1);

// Event Sound Functions
void buzzerReady();
void buzzerArmed();
void buzzerEmergency();
void buzzerKillSwitch();
void buzzerNoSignal();
void buzzerFrameLost();
void buzzerStartup();

// Initialize buzzer pin
void setupBuzzer()
{
    pinMode(BUZZER_PIN, OUTPUT);
    buzzerOff();
}

// Generate tone at specific frequency
void buzzerTone(int frequency, int duration)
{
    if (frequency > 0)
    {
        // Calculate period in microseconds
        int period = 1000000 / frequency;
        int halfPeriod = period / 2;

        // Generate square wave for specified duration
        unsigned long startTime = millis();
        while (millis() - startTime < duration)
        {
            digitalWrite(BUZZER_PIN, HIGH);
            delayMicroseconds(halfPeriod);
            digitalWrite(BUZZER_PIN, LOW);
            delayMicroseconds(halfPeriod);
        }
    }
    else
    {
        delay(duration); // Silent pause
    }
}

// Turn buzzer off
void buzzerOff()
{
    digitalWrite(BUZZER_PIN, LOW);
}

// Generate beep pattern
void buzzerBeep(int frequency, int duration, int count)
{
    for (int i = 0; i < count; i++)
    {
        buzzerTone(frequency, duration);
        if (i < count - 1)
        { // Don't pause after last beep
            delay(BEEP_PAUSE);
        }
    }
}

// Event Sound Functions
void buzzerReady()
{
    buzzerBeep(TONE_READY, BEEP_SHORT, 1); // Single short beep
}

void buzzerArmed()
{
    buzzerBeep(TONE_ARMED, BEEP_SHORT, 2); // Two quick high beeps
}

void buzzerEmergency()
{
    // Urgent pattern: 3 long low beeps
    buzzerBeep(TONE_EMERGENCY, BEEP_LONG, 3);
}

void buzzerKillSwitch()
{
    // Warning pattern: 2 medium beeps
    buzzerBeep(TONE_KILL_SWITCH, BEEP_MEDIUM, 2);
}

void buzzerNoSignal()
{
    // Alert pattern: 4 short beeps
    buzzerBeep(TONE_NO_SIGNAL, BEEP_SHORT, 4);
}

void buzzerFrameLost()
{
    // Quick warning: 1 medium beep
    buzzerBeep(TONE_FRAME_LOST, BEEP_MEDIUM, 1);
}

void buzzerStartup()
{
    // Startup melody: Low to high
    buzzerTone(TONE_EMERGENCY, BEEP_SHORT);
    delay(50);
    buzzerTone(TONE_NO_SIGNAL, BEEP_SHORT);
    delay(50);
    buzzerTone(TONE_STARTUP, BEEP_MEDIUM);
}

#endif