# DripLogic

A node based smart watering system using MAC addres based wireless communication between a main module and separate node modules with theoritically no limit for how many nodes it can use.

- [System Architecture](#system-architecture)
- [Bill of Materials](#bill-of-materials-bom--estimated-cost)
- [Hardware Design (KiCad)](#hardware-design-kicad)
- [Software Stack & Firmware](#software-stack--firmware)
- [Project Journal & Media](#project-journal--media)
- [Getting Started](#getting-started)

## System Architecture

DripLogic uses two or more hardware units that communicate without a router, using ESP-NOW.

### Master Unit

- ESP32-C3 SuperMini
  - I2C header J1
  - LED D1 on GPIO3 with a 220 Ω resistor
  - button SW1 on GPIO2 to GND
<img width="2364" height="1285" alt="image" src="https://github.com/user-attachments/assets/af4ebbd9-9c0e-4512-90c0-05ba14a42f74" />

### Watering Node

- ESP32-C3 SuperMini
  - Capacitive soil moisture sensor J1 on GPIO0
  - 5V/12V solenoid valve J2
  - N-channel MOSFET Q1
  - 10 kΩ pull-down resistor R1
  - 1N4007 flyback diode D1 for inductive spike protection
<img width="2363" height="1282" alt="image" src="https://github.com/user-attachments/assets/d73be98a-dab0-44e5-9e92-f0943f9f29a1" />

## BOM and Costs

Total price for Master + a node is 28 usd + shipping,

| Part | Description | QTY | Unit Price (USD) | Total Price (USD) | Vendor |
|------|-------------|----:|-----------------:|------------------:|--------|
| ESP32-C3-SUPERMINI | Main controllers for both main and node PCBs | 2 | 3.28 | 6.56 | HESTORE |
| SOILCAP-V20 | Capacitive soil moisture sensor | 1 | 2.15 | 2.15 | HESTORE |
| AO3400A | N-channel MOSFET for valve control | 1 | 2.55 | 2.55 | HESTORE |
| WSV-12V | 1/2 inch NC 12V DC solenoid valve | 1 | 7.88 | 7.88 | HESTORE |
| 1N4007 | Flyback diode for inductive spike suppression | 1 | 1.26 | 1.26 | HESTORE |
| 10K 5% | Pull-down resistor for MOSFET gate | 1 | 1.00 | 1.00 | HESTORE |
| MP1584EN-LF | 12V to 5V step-down buck converter module | 1 | 3.87 | 3.87 | HESTORE |
| AC142R-02P-5.08 | 5.08mm terminal blocks for power and valve | 2 | 0.66 | 1.32 | HESTORE |
| ZL201-08G (WWS8G) | 2.54mm 1x8 female headers for ESP32-C3 socketing | 4 | 0.25 | 1.00 | HESTORE |
| Tax & Shipping | Tax and shipping for the whole order | 1 | 3.85 | 3.85 | HESTORE |
| **TOTAL** | | **15** | | **31.44** | |

ESP32-C3 SuperMini 2 piece
Capacitive Soil Sensor 1 piece
Solenoid Valve 1 piece
MOSFET 1 piece
Resistor, Diode, led, button 1 piece

## Hardware Design

- Designed the pcb layouts in kicad
- Fully checked with DRC and ERC

## Software

- Language: MicroPython
- Wireless: ESP-NOW
- Tools used: Flashed with esptool.py and managed using the VS Code MicroPico extension
- Python code boot.py (initializes esp-NOW) and main.py (reads moisture, sends data, receives data, sends commands, receives commands. 

## Project Journal

Created as part of a Hack Club project documenting the journey:

journalling is in JOURNAL.md
## Getting Started

1. Clone the repo

   
   git clone https://github.com/Vlebi/smart-watering.git
   

   Flash MicroPython to your ESP32-C3 SuperMini boards using esptool.py.
3. Transfer boot.py and main.py to the Master and Node units using MicroPico.
4. Follow the KiCad schematics to solder your boards, mount the sensors, and connect the solenoid valves.
