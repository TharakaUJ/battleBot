#include "pins.h"
#include "motor_control.h"
#include <Arduino.h>
#include "receiver.h"
#include "restart.h"

unsigned long lastSignalTime = 0; // Tracks last valid SBUS data
int prevWeapon = -1;              // Stores previous weapon value
bool weaponArmed = false;         // Tracks if weapon is armed
bool lastWeaponState = false;

void setup()
{
    Serial.begin(115200);
    delay(1000);  // Give time for serial to initialize
    Serial.println("BattleBot starting up with ESC weapon control");

    // Initialize receiver
    setupReceiver();  // Fixed spelling

    /* Initialize motors and ESC */
    setupMotors();
    
    // Optional: Uncomment to run ESC calibration on first boot
    // Serial.println("Starting ESC calibration routine...");
    // calibrateWeaponESC();
    
    Serial.println("Motors and ESC initialized");
    
    // Send neutral signal to ESC to ensure proper startup
    controlWeapon(0);
    delay(500);  // Give ESC time to initialize
    
    Serial.println("System ready!");
}

void loop()
{
    if (sbus_rx.Read())
    {
        /* Get SBUS data */
        data = sbus_rx.data();
        lastSignalTime = millis(); // Update last valid signal time

        // Map SBUS values to motor control range
        int throttle = map(data.ch[THROTTLE_CHANNEL], 172, 1811, 255, -255); // CH1: Throttle
        int steering = map(data.ch[STEERING_CHANNEL], 172, 1811, 255, -255); // CH2: Steering

        // 3-state switch (-1, 0, 1) -1 is the off state.
        int weaponState = (data.ch[WEAPON_STATE_CHANNEL] > 1000) ? 1 : -1; // 2-state switch: -1 (OFF), 1 (ON)

        int weapon = map(data.ch[WEAPON_CHANNEL], 172, 1811, 0, 255); // CH3: Weapon control (0-255 range for ESC)
        bool killSwitch = (data.ch[KILL_SWITCH_CHANNEL] > 1000);      // CH6: Kill switch

        // Invert steering if that channel is high
        if (data.ch[STEERING_INVERT_CHANNEL] > 1000)
        {
            steering = -1 * steering;
            throttle = -1 * throttle;
        }

        /* Noise Filtering */
        if (abs(throttle) < NOISE_THRESHOLD)
            throttle = 0;
        if (abs(steering) < NOISE_THRESHOLD)
            steering = 0;
        if (weapon < NOISE_THRESHOLD)
            weapon = 0;

        /* Handle failsafe conditions */
        if (data.failsafe || killSwitch)
        {
            Serial.println("⚠️ EMERGENCY STOP! FAILSAFE or KILL SWITCH ACTIVE! ⚠️");
            throttle = 0;
            steering = 0;
            weapon = 0;

            // Immediately stop all motors
            controlMotors(0, 0);
            controlWeapon(0);  // ESC to neutral position
            
            // Disarm weapon for safety
            weaponArmed = false;

            restart(); // Restart system if kill switch is toggled
        }

        if (data.lost_frame)
        {
            Serial.println("⚠️ FRAME LOST! ⚠️");
        }

        /* Send values to motor control */
        controlMotors(throttle, steering);

        /* Weapon ESC Control Logic */
        if (weapon != prevWeapon || weaponState != lastWeaponState)
        {
            int escValue;
            
            if (weaponState == -1) { 
                // Weapon OFF state
                escValue = 0;  // Neutral signal
                weaponArmed = false;
                Serial.println("Weapon: OFF");
            }
            else if (weaponState == 1) {
                // Weapon ON state with direction 1
                escValue = -1 * weapon;  // Negative = reverse direction
                
                // Arm notification (once)
                if (!weaponArmed && weapon > 0) {
                    Serial.println("⚠️ WEAPON ARMED ⚠️");
                    weaponArmed = true;
                }
            }
            else {
                // Weapon ON state with direction 2
                escValue = weapon;  // Positive = forward direction
                
                // Arm notification (once)
                if (!weaponArmed && weapon > 0) {
                    Serial.println("⚠️ WEAPON ARMED ⚠️");
                    weaponArmed = true;
                }
            }

            // Update ESC with new value
            controlWeapon(escValue);
            prevWeapon = weapon;
            lastWeaponState = weaponState;
            
            // Debug ESC value
            if (escValue != 0) {
                Serial.print("Weapon ESC: ");
                Serial.print(escValue);
                Serial.print(" (");
                Serial.print(map(escValue, -255, 255, ESC_MIN_PULSE, ESC_MAX_PULSE));
                Serial.println(" µs)");
            }
        }

        /* Debug Output */
        Serial.print("Throttle: ");
        Serial.print(throttle);
        Serial.print("\tSteering: ");
        Serial.print(steering);
        Serial.print("\tWeapon: ");
        Serial.println(weapon);
        Serial.print("\tKill Switch: ");
        Serial.println(killSwitch ? "ON" : "OFF");
    }

    /* No Signal Timeout - If no SBUS data received in TIMEOUT_MS, stop the bot */
    if (millis() - lastSignalTime > TIMEOUT_MS)
    {
        Serial.println("⛔ NO SIGNAL! STOPPING BOT ⛔");
        controlMotors(0, 0); // Stop all motors
        controlWeapon(0);    // ESC to neutral position
        weaponArmed = false; // Disarm weapon
    }
}