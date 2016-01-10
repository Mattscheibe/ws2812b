/*
* ws2812b lib V1.0a: Programming interface for controlling WS2812B RGB LEDs
*
* assembler routine derived from light weight WS2812 lib V2.1 by Tim (cpldcpu@gmail.com)
*
* Author: Chris (Mattscheibenpost@gmail.com)
*
* June 24th, 2015 V1.0a Initial Version
*
* License: GNU GPL v2 (see License.txt)
*
* Edit ws2812b_config.h for setting up wiring scheme and data output pin.
*/
#ifndef _ws2812b_h_
#define _ws2812b_h_
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ws2812b_config.h"
struct cRGB {
  unsigned char g;
  unsigned char r;
  unsigned char b;
}; // = Struct for color values of one pixel
struct cRGB pixel[ WIDTH * HEIGHT ];// = array with all pixel color values
unsigned char maxBrightnessLEDs; // either change with setMaxBrightness(0...255) or by setting it directly
volatile unsigned char maskhi, masklo;
unsigned int idx(unsigned int row, unsigned int column); // gets index (offset) in a (linearily wired) strand
#define CONCAT(a, b)            a ## b
#define CONCAT_EXP(a, b)   CONCAT(a, b)
#define ws2812b_PORTREG CONCAT_EXP(PORT,ws2812b_Port)
#define ws2812b_DDRREG   CONCAT_EXP(DDR,ws2812b_Port)
void setRGB(unsigned int row, unsigned int column, unsigned long int color);
void setR(unsigned int row, unsigned int column, unsigned char red);
void setG(unsigned int row, unsigned int column, unsigned char green);
void setB(unsigned int row, unsigned int column, unsigned char blue);
unsigned long int getRGB(unsigned int row, unsigned int column);
unsigned char getR(unsigned int row, unsigned int column);
unsigned char getG(unsigned int row, unsigned int column);
unsigned char getB(unsigned int row, unsigned int column);
void setMaxBrightness(unsigned char value);
void clearLEDs(); // all LEDs off
void initLEDs();  // should be called once at the beginning of any program
void showLEDs();  // lights up strand with stored color value ( => displays values)
#define delay _delay_ms
#endif
