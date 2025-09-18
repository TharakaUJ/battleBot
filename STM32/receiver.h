#ifndef RECEIVER_H
#define RECEIVER_H

#include "sbus.h"
#include <Arduino.h>
#include "pins.h"

// For STM32 BluePill, use Serial1 for SBUS communication
// Serial1 uses PA9 (TX) and PA10 (RX) pins
// On STM32 BluePill, hardware Serial1 is fixed to PA9 (TX) and PA10 (RX).
// To use different pins, you must use a different hardware serial (e.g., Serial2) or use a software serial library.
// Example for Serial2 (PA2 TX, PA3 RX):
// bfs::SbusRx sbus_rx(&Serial2);

// If you want to use custom pins, consider using a software serial implementation (not recommended for SBUS due to timing).
bfs::SbusRx sbus_rx(&Serial1); // PA9 (TX), PA10 (RX) for STM32 BluePill
bfs::SbusData data;

void setupReceiver()
{
    /* Start SBUS communication on Serial1 */
    sbus_rx.Begin();
    Serial2.println("SBUS Receiver Started on STM32 BluePill!");
    Serial2.println("SBUS connected to Serial1 (PA10)");
    
    // Optional: Set up pin modes explicitly (usually handled by SBUS library)
    pinMode(S_BUS_IN, INPUT);
    
    Serial2.println("Waiting for SBUS signal...");
}

#endif
