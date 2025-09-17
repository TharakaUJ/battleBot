#ifndef RESTART_H
#define RESTART_H

#include "receiver.h"
#include "pins.h"
#include <Arduino.h>

#define TOGGLE_COUNT 3   // Number of toggles required
#define TIMEOUT_MS 2000  // Time window in milliseconds

void restart()
{
    int toggleCount = 0;
    unsigned long startTime = millis();
    bool lastKillState = false; // Store last state of kill switch

    Serial.println("🔄 Restart mode activated. Toggle kill switch to restart.");
    
    // Flash LED rapidly to indicate restart mode
    for (int i = 0; i < 10; i++) {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        delay(100);
    }

    while (true)  // Stay here until restart
    {
        if (sbus_rx.Read()) // Check if SBUS data is available
        {
            data = sbus_rx.data();
            bool killSwitch = (data.ch[KILL_SWITCH_CHANNEL] > 1000); // CH6: Kill switch

            if (killSwitch != lastKillState) // Detect a toggle
            {
                toggleCount++;
                lastKillState = killSwitch;
                Serial.print("Kill switch toggled: ");
                Serial.print(toggleCount);
                Serial.print("/");
                Serial.println(TOGGLE_COUNT);
                
                // Flash LED on each toggle
                digitalWrite(LED_PIN, LOW);
                delay(50);
                digitalWrite(LED_PIN, HIGH);
                delay(50);

                if (toggleCount >= TOGGLE_COUNT)
                {
                    Serial.println("✅ Restart confirmed! Rebooting system...");
                    
                    // Flash LED rapidly before restart
                    for (int i = 0; i < 20; i++) {
                        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
                        delay(50);
                    }
                    
                    // For STM32, we can use NVIC_SystemReset() or just return to main loop
                    // Since we don't have direct reset function, we'll just return
                    Serial.println("🚀 System restarted!");
                    return; // Exit restart mode and return to main loop
                }

                startTime = millis(); // Reset timeout
            }
        }

        // Check for timeout
        if (millis() - startTime > TIMEOUT_MS)
        {
            Serial.println("⏰ Restart timeout. Continuing normal operation...");
            return; // Exit restart mode
        }

        delay(10); // Small delay to prevent excessive CPU usage
    }
}

#endif
