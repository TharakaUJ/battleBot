# STM32 BluePill Battle Bot

This is the STM32 BluePill version of the battle bot controller, adapted from the original ESP32 code.

## Hardware Setup

### STM32 BluePill (STM32F103C8T6)
- **MCU**: STM32F103C8T6
- **Flash**: 64KB
- **RAM**: 20KB
- **Clock**: 72MHz

### Pin Connections

#### SBUS Receiver
- **SBUS Signal**: PA10 (Serial1 RX)
- **VCC**: 5V or 3.3V (depending on receiver)
- **GND**: GND

#### Motor Drivers (BTS7960)

**Right Motor Driver:**
- RRPWM: PA0
- RLPWM: PA1
- REN: PA8
- VCC: 5V-27V
- GND: GND

**Left Motor Driver:**
- LRPWM: PA2
- LLPWM: PA3
- LEN: PA9
- VCC: 5V-27V
- GND: GND

**Weapon Motor Driver:**
- WRPWM: PB0
- WLPWM: PB1
- WEN: PB10
- VCC: 5V-27V
- GND: GND

#### Status LED
- Built-in LED: PC13 (active low)

## Software Requirements

### Arduino IDE Setup
1. Install STM32 Arduino Core:
   ```
   https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
   ```

2. Install SBUS Library:
   - Install "Bolder Flight Systems SBUS" library

### Arduino CLI Setup
```bash
# Add STM32 board manager URL
arduino-cli config add board_manager.additional_urls https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json

# Update index
arduino-cli core update-index

# Install STM32 core
arduino-cli core install STMicroelectronics:stm32

# Install SBUS library
arduino-cli lib install "Bolder Flight Systems SBUS"
```

## Compilation and Upload

### Using Arduino CLI
```bash
# Compile
arduino-cli compile --fqbn STMicroelectronics:stm32:GenF1:pnum=BLUEPILL_F103C8 /path/to/STM32/

# Put BluePill in DFU mode (hold BOOT0, press RESET, release RESET)
# Check DFU mode
lsusb | grep -i dfu

# Upload using DFU
dfu-util -a 0 -s 0x08000000:leave -D /path/to/STM32/build/STMicroelectronics.stm32.GenF1/STM32.ino.bin
```

### Serial Monitor
After upload, connect USB-TTL converter to:
- TX: PA9 (Serial1 TX)
- RX: PA10 (Serial1 RX) - **Note: This conflicts with SBUS, use USB Serial instead**
- GND: GND

Monitor using:
```bash
arduino-cli monitor -p /dev/ttyUSB0 -c baudrate=115200
```

## Key Differences from ESP32 Version

1. **Pin Assignments**: Adapted to STM32 BluePill GPIO pins
2. **Serial Communication**: Uses Serial1 for SBUS (PA9/PA10)
3. **PWM Pins**: Uses STM32-compatible PWM pins
4. **LED Indication**: Uses built-in LED (PC13) for status
5. **Restart Function**: Adapted for STM32 (returns to main loop instead of ESP.restart())

## Channel Mapping

- **Channel 0**: Steering
- **Channel 1**: Throttle  
- **Channel 2**: Weapon Control
- **Channel 5**: Kill Switch
- **Channel 6**: Weapon State (3-position switch)
- **Channel 7**: Steering Invert

## Safety Features

- **Failsafe**: Stops all motors if SBUS failsafe is triggered
- **Kill Switch**: Emergency stop via dedicated channel
- **Signal Timeout**: Stops bot if no signal received for 500ms
- **Noise Filter**: Ignores small input values (< 15)
- **Restart Protection**: Requires multiple kill switch toggles to restart

## Troubleshooting

1. **No Serial Output**: Make sure STM32 core is properly installed
2. **No SBUS Signal**: Check wiring to PA10 and receiver power
3. **Motors Not Working**: Verify BTS7960 connections and power supply
4. **Compilation Errors**: Ensure all libraries are installed

## Power Requirements

- **STM32**: 3.3V (via USB or external regulator)
- **Motors**: 5V-27V (depending on motors used)
- **Logic**: 3.3V or 5V tolerant pins
