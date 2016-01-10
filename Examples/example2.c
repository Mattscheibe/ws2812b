// Blink one single WS2812B LED:
#include "ws2812b.h"
void main() {
  initLEDs(); // initialisation of strand, as defined in ws2812b.h --> port pin needs to be set there ! ! !
  setMaxBrightness(10); // relatively low, good for the eyes
  // repeat endlessly for blinking:
  while (1) {				 
    setRGB(0,0,0xFF9922);showLEDs(); // "on" -  some color
    _delay_ms(200);									 // pause a little
    setRGB(0,0,0x000000);showLEDs(); // "off" - might as well use clearLEDs();
    _delay_ms(500);									 // pause a little more
  }
}
