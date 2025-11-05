/*
 * ESP32 LED Switch Control via PC817 Optocoupler
 *
 * This sketch detects fast pulses from a PC817 optocoupler.
 *
 * Hardware connections:
 * - GPIO4: PC817 output (Collector to GPIO4, Emitter to GND)
 * - GPIO5: LED output (LED with appropriate current-limiting resistor)
 *
 * PC817 Input: 24V circuit → 1.2kΩ → PC817 LED (19mA)
 *
 * Operation:
 * - When PC817 conducts (24V pulse active), GPIO4 reads LOW and LED turns ON
 * - When PC817 is off, GPIO4 reads HIGH (pullup) and LED turns OFF
 * - Optimized for fast pulse detection (50-200ms pulses at 0.5-2.5 Hz)
 */

// Define pin numbers
const int SWITCH_PIN = 4;  // GPIO4 for switch input
const int LED_PIN = 5;     // GPIO5 for LED output

void setup() {
  // Configure GPIO4 as input with internal pullup resistor enabled
  // The pullup resistor keeps the pin HIGH when PC817 is off
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  // Configure GPIO5 as output for controlling the LED
  pinMode(LED_PIN, OUTPUT);

  // Initialize LED to OFF state
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Read the current state of the PC817 optocoupler
  // When 24V pulse is active (PC817 conducts): reads LOW (0)
  // When 24V pulse is off (PC817 open): reads HIGH (1) due to pullup
  int switchState = digitalRead(SWITCH_PIN);

  // Control LED based on optocoupler state
  // Direct mapping - no delay for fastest pulse detection
  if (switchState == LOW) {
    digitalWrite(LED_PIN, HIGH);  // Turn LED ON
  } else {
    digitalWrite(LED_PIN, LOW);  // Turn LED OFF
  }

  // No delay - loop runs as fast as possible to catch short pulses (50-200ms)
}
