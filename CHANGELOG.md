# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- PWM brightness ramping based on pulse duration (2024-11-05)
- Gradual brightness increase for longer pulses
- Configurable brightness parameters (MIN_BRIGHTNESS, MAX_BRIGHTNESS, RAMP_TIME_MS)
- STATUS.md for tracking development progress
- README.md with comprehensive documentation

### Changed
- Updated from simple on/off LED control to PWM brightness ramping
- Removed delay from loop() for optimal pulse detection and smooth ramping

## [1.0.0] - 2024-11-05

### Added
- Initial working implementation
- PC817 optocoupler support for 24V drum trigger isolation
- Fast pulse detection (50-200ms pulses at 0.5-2.5 Hz)
- Direct LED control with INPUT_PULLUP on GPIO4
- Simple on/off LED switching via GPIO5
- No delay in main loop for responsive detection

### Technical Details
- ESP32 LEDC PWM peripheral (8-bit, 5kHz)
- GPIO4: PC817 input with internal pullup
- GPIO5: LED output
- Optimized for fast pulse detection

[Unreleased]: https://github.com/ronHartikka/esp32-led-switch/compare/v1.0.0...HEAD
[1.0.0]: https://github.com/ronHartikka/esp32-led-switch/releases/tag/v1.0.0
