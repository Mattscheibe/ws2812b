# ws2812b

A library for driving WS2812b based (aka Neopixel) LED strands on an AVR controller or Arduino-like board. Allows for convenient setup of matrix-like displays. Uses standard addressing and standard color coding like in image processing. For code interchange, this library also exists for Arduino boards (supports more than one strand) and for Raspberry Pi.

---

Data transfer routine is taken from library https://github.com/cpldcpu/light_ws2812.
User interface is simplified and unified for all platforms.

---

## Hardware Setup
* Supports one output pin (to be configured in header file).
* A resistor of 220...470 ohms should be used for connecting microcontroller pin and WS2812B LED pin.
* For longer strands, a capacitor of 100uF should be added to +5V and GND of strand.
* Config file ws2812b_config.h declares which AVR pin will be used for connecting to the strand.
* Standard setting is for a linear strand connected to pin D12 of an Arduino Nano board.
* Clock frequency should be 8MHz (for AVR controllers) or 16MHz (for Arduino boards).
* Find all possible wiring schemes in file ws2812b_config.h.

## Workflow
(_If needed, first edit Makefile and set preferred editor._)

* Copy all .c and .h files and the Makefile to a new directory.
* Type "make config" and set which port pin and which wiring scheme is being used.
* Type "make make" and set file names for your project.
* Type "make edit" and edit main program or type "make editall" and edit all files.
* Type "make prog" in order to compile and transfer your programm.
  (or just type "make" for testing only)

---

## Commands

```
initLEDs();                   // attach strand to controller
                              // please add this at the beginning of your program

setR(row,column,color);       // set red value for pixel at matrix position row,column
                              // column should be zero for single linear strands
                              // color ranges from 0x00 to 0xFF

setG(row,column,color);       // dito for green value

setB(row,column,color);       // dito for blue value

setRGB(row,column,fullcolor); // set all three color values at once
                              // full color ranges from 0x000000 to 0xFFFFFF
                              // values can be taken from image processing or color picker tools

getR(row,column);             // read-out function for red channel of addressed pixel
                              // possible range from 0x00...0xFF

getG(row,column);             // dito for green channel

getB(row,column);             // dito for blue channel

getRGB(row,column);           // read-out function for full color value of addressed pixel
                              // possible range from 0x000000 to 0xFFFFFF

showLEDs();                   // will display all pixels (with the colors that have been set before)

clearLEDs();                  // reset all color values to 0 and display a "blank screen"

setMaxBrightness(maxValue);   // used for dimming (good to the eyes!)
                              // maxValue ranges from 0x00 (full dimming) to 0xFF (no dimming)
                              // will usually be called once at the beginning of the program 
                              // but can also be called several times for special effects
                              // good values for maxValue while prototyping are 3...10
                              // will change intensity of display by limiting color resolution
                              // will effect all subsequent calls to showLEDs()
```