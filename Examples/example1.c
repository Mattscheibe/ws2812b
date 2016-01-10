// Use a strand of three LEDs to display some red, green and blue respectively
#include "ws2812b.h"
void main() {
  initLEDs(); // initialisation of strand, as defined in ws2812b.h --> port pin needs to be set there ! ! !
  setRGB(0,0,0xFF0000); // pixel 0,0 as red
  setRGB(1,0,0x00FF00); // pixel 1,0 as green 
  setRGB(2,0,0x0000FF); // pixel 2,0 as blue
  setMaxBrightness(5); // dim down to 5 = low brightness
  showLEDs(); // display all color values now
}
