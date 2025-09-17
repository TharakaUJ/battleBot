#ifndef RECEIVER_H
#define RECEIVER_H

#include "sbus.h"
#include <Arduino.h>
#include "pins.h"

// For STM32 BluePill, use Serial1 for SBUS communication
// Serial1 uses PA9 (TX) and PA10 (RX) pins
bfs::SbusRx sbus_rx(&Serial1);
bfs::SbusData data;

void setupReceiver()
{
    /* Start SBUS communication on Serial1 */
    sbus_rx.Begin();
    Serial.println("SBUS Receiver Started on STM32 BluePill!");
    Serial.println("SBUS connected to Serial1 (PA10)");
    
    // Optional: Set up pin modes explicitly (usually handled by SBUS library)
    pinMode(S_BUS_IN, INPUT);
    
    Serial.println("Waiting for SBUS signal...");
}

#endif
