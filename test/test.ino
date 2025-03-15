#include <Arduino.h>

#define PWM_INPUT_PIN 34  // Connect this to one of the receiver's PWM outputs

void setup() {
  Serial.begin(115200);
  pinMode(PWM_INPUT_PIN, INPUT);
}

void loop() {
  unsigned long duration = pulseIn(PWM_INPUT_PIN, HIGH);
  Serial.print("PWM Pulse Width: ");
  Serial.println(duration);
  delay(50);
}
