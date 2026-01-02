#  Ultrasonic Distance Display with 8x8 LED Matrix

## Overview
A smart Arduino-based distance measurement system that visually displays proximity using an 8x8 LED matrix. When objects come within 10cm of the ultrasonic sensor, the system shows the exact distance (0-9 cm) in real-time on the LED display.
DEMO VIDEO
[https://github.com/prince867-ux/Distance-calculator-Arduino/blob/main/demo_dist_clac.mp4]
## Features
- ✅ Real-time distance measurement (0-400 cm range)
- ✅ Visual display on 8x8 LED matrix when distance < 10cm
- ✅ Clear digit display (0-9) for accurate readings
- ✅ Multiple visual indicators for different distance ranges
- ✅ Serial monitor logging for debugging
- ✅ Startup animation sequence
- ✅ Adjustable sensitivity and brightness
- ✅ Buzzer alarm for distance>9cm

##  Components Required

### Hardware
| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino Uno/Nano | 1 | Any Arduino compatible board |
| HC-SR04 Ultrasonic Sensor | 1 | 2cm-400cm range, 3mm accuracy |
| 8x8 LED Matrix with MAX7219 | 1 | Common anode, with driver IC |
| Jumper Wires | 10-15 | Male-to-Male |
| Breadboard | 1 | Standard 400/830 points |
| USB Cable | 1 | For Arduino programming |
| Power Supply | 1 |buzzer|

### Software
- Arduino IDE (v1.8.19 or later)
- LedControl Library (by Eberhard Fahle)

### Pin Connections

 Arduino setup
5v--------->breadboard +ve rail
GND-------->Breadboard -ve rail
I/O PIN3--->BUZZER +VE
I/O PIN8--->MAX7219 DIN
I/O PIN9--->MAX7219 CS
I/O PIN10-->MAX7219 CLK
I/O PIN11-->HCRS04 TRIGGER
I/O PIN12-->HCRS04 ECHO

 COMPONENT SETUP
BUZZER-VE-->-VE RAIL
HCRS04 GND-->-RAIL
MAX7219 GND-->-VE RAIL
HCRS04 VCC-->+VE RAIL 
MAX7219----->+VE RAIL

AUTHOR~ Priyanshu kewat
