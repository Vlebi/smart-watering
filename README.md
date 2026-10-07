# DripLogic

A modular, dual-unit wireless smart irrigation system built with **ESP32-C3** microcontrollers, **MicroPython**, and **ESP-NOW** peer-to-peer communication. Designed from scratch in **KiCad** for low-power, automated plant care.

## Table of Contents

- [System Architecture](#system-architecture)
- [Bill of Materials](#bill-of-materials-bom--estimated-cost)
- [Hardware Design (KiCad)](#hardware-design-kicad)
- [Software Stack & Firmware](#software-stack--firmware)
- [Project Journal & Media](#project-journal--media)
- [Getting Started](#getting-started)

## System Architecture

DripLogic consists of two hardware units that communicate wirelessly, without a router, using ESP-NOW.

### Master Unit

- **Microcontroller:** ESP32-C3 SuperMini
- **User interface:**
  - I2C OLED display header (`J1`)
  - Status LED (`D1`) on GPIO3 via a 220 Ω resistor
  - Tactile push button (`SW1`) on GPIO2 to GND
- **Role:** Coordinates sensor polling, processes soil moisture states, and triggers irrigation commands.

### Watering Node

- **Microcontroller:** ESP32-C3 SuperMini
- **Sensors & actuators:**
  - Capacitive soil moisture sensor (`J1`) on GPIO0 (ADC)
  - 5V/12V solenoid valve (`J2`)
- **Driver circuitry:**
  - N-channel MOSFET (`Q1`) for valve switching
  - 10 kΩ pull-down resistor (`R1`) for a safe gate state
  - 1N4007 flyback diode (`D1`) for inductive spike protection

## Bill of Materials (BOM) & Estimated Cost

Total estimated budget for **1 Master + 1 Node** is approximately **$49.50 USD (~18,310 HUF)**, sourced locally from suppliers such as HEStore and HQ Electronics.

| Component | Description | Qty |
| --- | --- | :---: |
| ESP32-C3 SuperMini | Compact Wi-Fi/BLE microcontroller | 2 |
| I2C OLED Display | Status and telemetry readout | 1 |
| Capacitive Soil Sensor | Corrosion-resistant moisture detection | 1 |
| Solenoid Valve | 5V/12V gravity-feed compatible valve | 1 |
| N-Channel MOSFET | Switching transistor (e.g., IRLZ44N or equivalent) | 1 |
| Passives & Diodes | 10 kΩ resistor, 220 Ω resistor, 1N4007 diode | 1 set |
| Misc. Hardware | Push button, status LED, headers, PCB fabrication | 2 sets |

## Hardware Design (KiCad)

- **Schematic capture & PCB layout:** Designed in KiCad with custom footprints for the ESP32-C3 SuperMini, optimized signal routing, proper power flags (`PWR_FLAG`), and a robust MOSFET-driven inductive load stage.
- **Verification:** Fully checked with Design Rule Checks (DRC) to ensure zero shorts on the 5V and ground rails.

## Software Stack & Firmware

- **Language:** MicroPython
- **Wireless protocol:** ESP-NOW (ultra-low latency, router-free peer communication)
- **Toolchain:** Flashed with `esptool.py` and managed using the VS Code MicroPico extension
- **Structure:** Modular scripts (`boot.py` and `main.py`) handling deep sleep cycles, ADC moisture reads, and interrupt-driven valve actuation

## Project Journal & Media

Created as part of a **Hack Club** project journal documenting the end-to-end engineering journey:

- **Timelapses & CAD renders:** Visualizing the PCB layout and soldering process
- **Idea reel:** A short showcase video introducing DripLogic in action

## Getting Started

1. **Clone the repository**

   ```bash
   git clone https://github.com/Vlebi/smart-watering.git
   ```

2. **Flash MicroPython** onto your ESP32-C3 SuperMini boards using `esptool.py`.
3. **Upload scripts:** Transfer `boot.py` and `main.py` to the Master and Node units using MicroPico.
4. **Assemble hardware:** Follow the KiCad schematics to solder your boards, mount the sensors, and connect the solenoid valves.
