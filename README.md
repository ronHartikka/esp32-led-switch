# ESP32 LED Switch

LED flash controller for drum triggers using an ESP32 and PC817 optocoupler. Converts 24V drum trigger pulses into LED flashes with **brightness proportional to pulse duration** - longer hits flash brighter!

## Features

- Fast pulse detection (50-200ms pulses at 0.5-2.5 Hz)
- PWM brightness ramping - longer pulses = brighter flashes
- Optocoupler isolation between 24V drum circuit and microcontroller
- No delay in main loop for responsive pulse detection
- Simple 2-wire connection to drum trigger circuit

## Hardware Requirements

### Components
- **ESP32 development board** (ESP32-D0WD-V3 or similar)
- **PC817 Optocoupler** (4-pin DIP)
- **1.2kΩ resistor** (for PC817 LED input, provides ~19mA at 24V)
- **LED + current-limiting resistor** (value depends on LED specs)
- **24V drum trigger circuit** (pulse output)

### Pin Connections

```
24V Drum Circuit:
  24V+ ──[1.2kΩ]──┬──> PC817 pin 1 (Anode)
                  │
  Trigger Pulse ──┘

  GND ────────────> PC817 pin 2 (Cathode)

ESP32 Connections:
  GPIO4 ──────────> PC817 pin 4 (Collector)
  GND ────────────> PC817 pin 3 (Emitter)
  GPIO5 ──────────> LED + Resistor ──> GND
```

### PC817 Pinout (looking at top of chip)
```
  ┌───────┐
  │ ●     │
1─┤ A   C ├─4  (Pin 1: Anode, Pin 4: Collector)
2─┤ K   E ├─3  (Pin 2: Cathode, Pin 3: Emitter)
  └───────┘
```

## How It Works

1. **Drum trigger fires** → 24V pulse activates PC817 LED
2. **PC817 conducts** → GPIO4 reads LOW (pulled to GND through optocoupler)
3. **PWM ramps up** → LED brightness increases gradually over 300ms
4. **Longer pulse = brighter flash** → Short hits are dimmer, hard hits are brighter
5. **Pulse ends** → LED immediately turns off

The internal pullup resistor on GPIO4 keeps the pin HIGH when the optocoupler is off.

## Software Setup

### Requirements
- Arduino IDE or arduino-cli
- ESP32 board support installed

### Arduino Board Manager Setup
1. Add ESP32 board manager URL: `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
2. Install "esp32" boards package
3. Select board: **"ESP32 Dev Module"** or your specific ESP32 board

### Configuration Options

In `esp32-led-switch.ino`, adjust these constants to tune behavior:

```cpp
// Lines 29-32
const int MIN_BRIGHTNESS = 20;   // Starting brightness (0-255)
const int MAX_BRIGHTNESS = 255;  // Maximum brightness (0-255)
const int RAMP_TIME_MS = 300;    // Time to reach max brightness (ms)
```

**Tuning Tips:**
- Increase `RAMP_TIME_MS` for slower, more gradual brightness changes
- Increase `MIN_BRIGHTNESS` to make short hits more visible
- Decrease `MAX_BRIGHTNESS` if LED is too bright at peak

### Upload Instructions

**Using arduino-cli:**
```bash
arduino-cli compile --fqbn esp32:esp32:esp32 .
arduino-cli upload -p /dev/tty.usbserial-0001 --fqbn esp32:esp32:esp32 .
```

**Important:**
- Close Arduino IDE Serial Monitor before uploading
- Use `/dev/tty.usbserial-XXXX` (not the `cu.` version which can get busy)
- ESP32 must be connected via USB

## Technical Details

### PWM Configuration
- **Resolution**: 8-bit (0-255 values)
- **Frequency**: 5000 Hz
- **Method**: ESP32 LEDC (LED Control) peripheral via `ledcAttach()` and `ledcWrite()`

### Pin Definitions
- **GPIO4**: Input with internal pullup enabled
- **GPIO5**: PWM output for LED control

## Troubleshooting

**LED doesn't light up:**
- Check LED polarity and current-limiting resistor
- Verify GPIO5 connection
- Test with a simple blink sketch first

**Pulses not detected:**
- Verify PC817 is conducting (check with multimeter)
- Ensure 1.2kΩ resistor is providing ~19mA to PC817 LED
- Check GPIO4 connection to pin 4 of PC817
- Verify GND connection between ESP32 and PC817 pin 3

**LED flickers or behaves erratically:**
- Ensure common ground between drum circuit and ESP32 (through PC817)
- Check for loose connections
- Verify 24V circuit provides clean pulses

**Upload fails:**
- Close Arduino IDE Serial Monitor if open
- Try different USB cable
- Hold BOOT button during upload (some boards)
- Check driver installation (CP210x or CH340 depending on board)

## GitHub Repository

This project is hosted at: https://github.com/ronHartikka/esp32-led-switch

## Related Projects

- **d1-mini-drum-flash** - ESP8266/D1 Mini version (smaller, cheaper alternative)

## License

Open source - use freely for any purpose.
