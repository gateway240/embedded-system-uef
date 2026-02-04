# Embedded Systems UEF - Spring 2026
This repository contains the code for the Embedded Systems course at UEF

## Exercise 1 - Introduction
- [Arduino Nano Every full pinout](https://docs.arduino.cc/resources/pinouts/ABX00028-full-pinout.pdf)
- Follow the [PWM DC Motor Guide](https://www.hackster.io/onedeadmatch/control-dc-motor-with-npn-transistor-arduino-pwm-cdaf2e), but use a lower resistance resistor 
for the fan (or it won't spin).

### Steps
Setup Arduino IDE for Nano Sense Every

1. Install the Arduino IDE:
    - [Arch Linux](https://wiki.archlinux.org/title/Arduino)
    - [Windows, macOS, and Ubuntu](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE)
2. Plug the board into your computer with the provided USB Micro B cable
3. [Configure the IDE for Nano Every](https://learn.pakronics.com.au/arduino/tutorials/setup-arduino-every-board-in-arduino-ide)
### Troubleshooting

- [”avrdude: jtagmkII_initialize(): Cannot locate "flash" and "boot" memories in description"](https://support.arduino.cc/hc/en-us/articles/4405239282578-If-you-see-a-jtagmkII-initialize-Cannot-locate-flash-and-boot-memories-in-description-message-when-uploading-to-Nano-Every)



## Exercise 2 - Accelerometer
Configure the OLED and accelerometer
### Steps


1. Install `Adafruit SSD1306 by Adafruit` in the Arduino IDE
2. Wire the OLED and Accelerometer to the SCL and SDA ports of the board. DO NOT use external pullup resistors with the OLED display. It won't work. Wire the 3.3V power output to the VCC line. DO NOT wire 5V to the accelerometer or it will kill the sensor.
### Troubleshooting

- 
## Exercise 3 - Gyroscope

### Steps


1.
### Troubleshooting

- 





