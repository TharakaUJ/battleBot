# BattleBot

BattleBot is a robotics project built on STM32 microcontrollers using the Arduino framework. This repository contains the source code and instructions to get started.

## Features

- STM32-based control
- Arduino-compatible codebase
- Example: Blinky sketch

## Getting Started

1. **Clone the repository:**

   ```sh
   git clone https://github.com/yourusername/battleBot.git
   cd battleBot
   ```

2. **Install Arduino CLI:**
   Follow instructions at [Arduino CLI documentation](https://arduino.github.io/arduino-cli/latest/installation/).

3. **Install STM32 core:**
   ```sh
   arduino-cli core update-index
   arduino-cli core install STMicroelectronics:stm32
   ```

## Compile

```sh
arduino-cli compile --fqbn STMicroelectronics:stm32:GenF1:upload_method=dfu2Method .
```

## Upload manually with dfu-util (since Arduino CLI upload isn't working directly)

```sh
dfu-util -d 1eaf:0003 -a 2 -D /home/tharaka/.cache/arduino/sketches/CA3311401B671416B78BBD3A3E964ACE/Blinky.ino.bin
```

Last time I check these are the working commands

```sh
 arduino-cli compile --fqbn STMicroelectronics:stm32:GenF1:pnum=BLUEPILL_F103CB,upload_method=dfu2Method,usb=CDC -v ./STM32/
```

```sh
dfu-util -d 0483:df11 -a 2 -D ~/.cache/path/STM32.ino.bin
```
