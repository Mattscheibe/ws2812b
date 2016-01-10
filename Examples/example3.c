// Change brightness on a single WS2812B LED:
#include "ws2812b.h"
#define PAUSE 30      // define how long we will wait after each update (-> cycling speed while "breathing")

void main() {
  initLEDs();         // initialisation of strand, as defined in ws2812b.h --> port pin needs to be set there ! ! !
  setR(0,0,0xFF);		  // only setting red channel (will leave other colors unset)
  unsigned int x;			// used for counting loops
  // do this repeatedly:
  while (1) {
    // change brightness ("pulse"):
    // 1st up:
    for (x=0;x<20;x++) {
      setMaxBrightness(x); // change brightness (color will remain red, because no new set command is being applied)
      showLEDs();          // show LED color with updated brightness
      _delay_ms(PAUSE);    // little pause for our lazy eyes
    }
    // 2nd down:
    for (x=20;x>0;x--) {
      setMaxBrightness(x);
      showLEDs();
      _delay_ms(PAUSE);
    } 
  }
}
