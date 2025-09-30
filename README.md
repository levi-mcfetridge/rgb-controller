# RGB-Controller

A microcontroller-based RGB LED controller built with **Arduino (C++)** and the **FastLED** library.  
This project allows real-time color control using potentiometers, with support for brightness and theme saving.

![rgb-control-clip](https://github.com/user-attachments/assets/0e8fb5d1-30db-411b-8d6c-38aa18fc59d8)
<p align="center">
  <a href="https://github.com/user-attachments/assets/0e8fb5d1-30db-411b-8d6c-38aa18fc59d8">
    <img src="https://github.com/user-attachments/assets/0e8fb5d1-30db-411b-8d6c-38aa18fc59d8" alt="LED strip demo clip" width="540">
  </a>
</p>
![box](https://github.com/user-attachments/assets/2ccdc36e-7628-4356-b48e-43289cb02091)
<p align="center">
  <a href="https://github.com/user-attachments/assets/2ccdc36e-7628-4356-b48e-43289cb02091">
    <img src="https://github.com/user-attachments/assets/2ccdc36e-7628-4356-b48e-43289cb02091" alt="3D printed enclosure" width="300">
  </a>
</p>
## Features
- Control RGB LED strips (WS2811/WS2812) with Arduino.
- Real-time adjustment of **Red, Green, and Blue** values via potentiometers.
- Adjustable brightness using analog input.
- Smooth blending and transitions powered by the FastLED library.

- Designed for custom hardware with a **3D-printed enclosure** (SolidWorks).

---

## Hardware Requirements
- Arduino (tested on Uno/Nano)
- WS2811/WS2812 LED strip (or compatible, 60 LEDs in example)
- 3x Potentiometers (one each for Red, Green, Blue channels)
- Optional: Buttons for saving/loading color themes
- 5V power supply
- 3D-printed enclosure (custom)

---

## Software Requirements
- [Arduino IDE](https://www.arduino.cc/en/software)
- [FastLED library](https://github.com/FastLED/FastLED)

Install the library via Arduino IDE:  
`Sketch > Include Library > Manage Libraries > Search "FastLED"`

---

## Getting Started
1. Clone this repository:
   ```bash
   git clone https://github.com/levi-mcfetridge/RGB-controller.git
   cd RGB-controller
