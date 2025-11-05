# ESP32 LED Switch Project Status

## Current Status
Working on PWM version with gradual brightness ramping. Code is written and compiled successfully, but needs to be uploaded to ESP32 for testing.

## What We've Done
1. ✅ Created initial working version (simple on/off LED control via PC817 optocoupler)
2. ✅ Removed delay from loop() for better pulse detection
3. ✅ Successfully uploaded and tested - works well
4. ✅ Set up Git repository
5. ✅ Created GitHub repository: https://github.com/ronHartikka/esp32-led-switch
6. ✅ Pushed initial working code to GitHub
7. ✅ Created PWM version with gradual brightness ramping (compiled successfully)

## Next Steps
1. Upload PWM version to ESP32 and test
2. Adjust brightness ramping parameters if needed (MIN_BRIGHTNESS, MAX_BRIGHTNESS, RAMP_TIME_MS)
3. Commit and push PWM version to GitHub once working

## Important Info

### Hardware
- ESP32-D0WD-V3
- GPIO4: PC817 optocoupler output (with INPUT_PULLUP)
- GPIO5: LED output
- PC817 input: 24V circuit → 1.2kΩ resistor → PC817 LED (19mA)

### Upload Port
**Use `/dev/tty.usbserial-0001`** (not the cu version - it gets busy)

### Upload Command
```bash
arduino-cli upload -p /dev/tty.usbserial-0001 --fqbn esp32:esp32:esp32 .
```

### Before Uploading
- Close Arduino IDE completely (or at least Serial Monitor)
- ESP32 needs to be plugged in

### PWM Parameters (in code)
Located around lines 30-33 in esp32-led-switch.ino:
- `MIN_BRIGHTNESS`: 20 (starting brightness, 0-255)
- `MAX_BRIGHTNESS`: 255 (peak brightness, 0-255)
- `RAMP_TIME_MS`: 300 (milliseconds to reach max brightness)

These can be adjusted to change how the brightness ramping behaves.

## Problem We're Solving
Longer flashes from the 24V circuit should appear brighter than short flashes. The PWM version gradually increases LED brightness based on how long the pulse has been active.

## GitHub CLI Setup
- Installed: `brew install gh`
- Authenticated: `gh auth login` (using HTTPS)
- Connected successfully
