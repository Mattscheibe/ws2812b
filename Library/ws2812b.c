/*
* ws2812b lib V1.0a: Programming interface for controlling WS2812B RGB LEDs
*
* assembler routine derived from light weight WS2812 lib V2.1 by Tim (cpldcpu@gmail.com)
*
* Author: Chris (Mattscheibenpost@gmail.com)
*
* January 10th, 2016 V1.0a Initial Version
*
* License: GNU GPL v2 (see file LICENSE)
*
* Edit ws2812b_config.h for setting up wiring scheme and data output pin.
*/
#include "ws2812b.h"
unsigned int idx(unsigned int i, unsigned int j) {
  // calculates offset for chosen wiring scheme:
  unsigned int x;
#if TYPE ==  0
  if (j%2 == 0) {
    x = j * HEIGHT + i ;
  } else {
    x = j * HEIGHT + ( HEIGHT - 1 - i ) ;
  }
#endif
#if TYPE ==  1
  x = j * HEIGHT + i ;
#endif
#if TYPE ==  2
   if ((WIDTH-j)%2 == 0) {
    x = ( WIDTH - 1 - j ) * HEIGHT + HEIGHT - 1 - i ;
  } else {
     x = ( WIDTH - 1 - j ) * HEIGHT + i ;
  }
#endif
#if TYPE ==  3
  x = ( WIDTH - 1 - j ) * HEIGHT + i ;
#endif
#if TYPE ==  4
  if (i%2 == 0) {
    x = i * WIDTH + j ;
  } else {
    x = i * WIDTH + ( WIDTH - 1 - j ) ;
  }
#endif
#if TYPE ==  5
  x = i * WIDTH + j;
#endif
#if TYPE ==  6
  if (i%2 == 0) {
    x = i * WIDTH + ( WIDTH - 1 - j ) ;
  } else {
    x = i * WIDTH + j ;
  }
#endif
#if TYPE ==  7
  x = i * WIDTH + ( WIDTH - 1 - j ) ;
#endif
#if TYPE ==  8
  if (j%2 == 0) {
    x = j * HEIGHT + ( HEIGHT - 1 - i ) ;
  } else {
    x = j * HEIGHT + i ;
  }
#endif
#if TYPE ==  9
  x = j * HEIGHT + ( HEIGHT - 1 - i ) ;
#endif
#if TYPE == 10
  if ((WIDTH-j)%2 == 0) {
    x = ( WIDTH - 1 - j ) * HEIGHT + i ;
  } else {
    x = ( WIDTH - 1 - j ) * HEIGHT + ( HEIGHT - 1 - i ) ;
  }
#endif
#if TYPE == 11
  x = ( WIDTH - 1 - j ) * HEIGHT + ( HEIGHT - 1 - i ) ;
#endif
#if TYPE == 12
  if ((HEIGHT-i)%2 == 0) {
    x = ( HEIGHT - 1 - i ) * WIDTH + ( WIDTH - 1 - j ) ;
  } else {
    x = ( HEIGHT - 1 - i ) * WIDTH + j ;
  }
#endif
#if TYPE == 13
  x = ( HEIGHT - 1 - i ) * WIDTH + j ;
#endif
#if TYPE == 14
  if ((HEIGHT-i)%2 == 0) {
    x = ( HEIGHT - 1 - i ) * WIDTH + j ;
  } else {
    x = ( HEIGHT - 1 - i ) * WIDTH + ( WIDTH - 1 - j ) ;
  }
#endif
#if TYPE == 15
  x = ( HEIGHT - 1 - i ) * WIDTH + ( WIDTH - 1 - j ) ;
#endif
  return x;
}
void setRGB(unsigned int i, unsigned int j, unsigned long int rgb) {
  unsigned char r,g,b;
  r = rgb >> 16;
  g = (rgb >> 8) & 0xFF;
  b = rgb & 0xFF;
  unsigned int x = idx(i,j);
  pixel[x].r=r;
  pixel[x].g=g;
  pixel[x].b=b;
}
void setR(unsigned int i, unsigned int j, unsigned char red) {
  unsigned int x = idx(i,j);
  pixel[x].r=red;
}
void setG(unsigned int i, unsigned int j, unsigned char green) {
  unsigned int x = idx(i,j);
  pixel[x].g=green;
}
void setB(unsigned int i, unsigned int j, unsigned char blue) {
  unsigned int x = idx(i,j);
  pixel[x].b=blue;
}
unsigned long int getRGB(unsigned int i, unsigned int j) {
  unsigned long int rgb;
  unsigned int x = idx(i,j);
  rgb = pixel[x].r << 16 + pixel[x].g << 8 + pixel[x].b;
  return rgb;
}
unsigned char getR(unsigned int i, unsigned int j) {
  unsigned int x = idx(i,j);
  return pixel[x].r;
}
unsigned char getG(unsigned int i, unsigned int j) {
  unsigned int x = idx(i,j);
  return pixel[x].g;
}
unsigned char getB(unsigned int i, unsigned int j) {
  unsigned int x = idx(i,j);
  return pixel[x].b;
}
void setMaxBrightness(unsigned char value) {
  maxBrightnessLEDs = value;
}
void initLEDs() {
  // please initially call once
  maskhi = _BV(ws2812b_Pin);
  masklo = ~maskhi & ws2812b_PORTREG;
  maskhi |= ws2812b_PORTREG;
  ws2812b_DDRREG |= (1<< ws2812b_Pin); // data pin as output
  maxBrightnessLEDs=255;
  clearLEDs();
}
void clearLEDs() {
  // all LEDs off
  int x;
  for (x=0;x<WIDTH*HEIGHT;x++) {
    pixel[x].r=0;
    pixel[x].g=0;
    pixel[x].b=0;
  }
  showLEDs();
}
// Timing in ns:
#define w_zeropulse   350
#define w_onepulse    900
#define w_totalperiod 1250
// Fixed cycles used by the inner loop:
#define w_fixedlow    3
#define w_fixedhigh   6
#define w_fixedtotal  10   
// Insert NOPs to match the timing, if possible:
#define w_zerocycles    (((F_CPU/1000)*w_zeropulse          )/1000000)
#define w_onecycles     (((F_CPU/1000)*w_onepulse    +500000)/1000000)
#define w_totalcycles   (((F_CPU/1000)*w_totalperiod +500000)/1000000)
// w1 - nops between rising edge and falling edge - low:
#define w1 (w_zerocycles-w_fixedlow)
// w2   nops between fe low and fe high
#define w2 (w_onecycles-w_fixedhigh-w1)
// w3   nops to complete loop
#define w3 (w_totalcycles-w_fixedtotal-w1-w2)
#if w1>0
  #define w1_nops w1
#else
  #define w1_nops  0
#endif
// The only critical timing parameter is the minimum pulse length of the "0"
// Warn or throw error if this timing can not be met with current F_CPU settings.
#define w_lowtime ((w1_nops+w_fixedlow)*1000000)/(F_CPU/1000)
#if w_lowtime>550
   #error "Light_ws2812: Sorry, the clock speed is too low. Did you set F_CPU correctly?"
#elif w_lowtime>450
   #warning "Light_ws2812: The timing is critical and may only work on WS2812B, not on WS2812(S)."
   #warning "Please consider a higher clockspeed, if possible"
#endif   
#if w2>0
#define w2_nops w2
#else
#define w2_nops  0
#endif
#if w3>0
#define w3_nops w3
#else
#define w3_nops  0
#endif
#define w_nop1  "nop      \n\t"
#define w_nop2  "rjmp .+0 \n\t"
#define w_nop4  w_nop2 w_nop2
#define w_nop8  w_nop4 w_nop4
#define w_nop16 w_nop8 w_nop8
void showLEDs() {
  // display pixel array content to LEDs
  float currentBrightness = (float)maxBrightnessLEDs / 255.0 ;
  unsigned char curbyte,ctr;
  unsigned char sreg_prev;
  unsigned int datlen=WIDTH*HEIGHT*3;
  unsigned char *data;
  if (maxBrightnessLEDs == 255) {
    data = (unsigned char *)pixel;
  } else {
    struct cRGB newpixel[WIDTH*HEIGHT];
    unsigned int x;
    for (x=0;x<WIDTH*HEIGHT;x++) {
      newpixel[x].r=(unsigned char)((float)pixel[x].r*currentBrightness);
      newpixel[x].g=(unsigned char)((float)pixel[x].g*currentBrightness);
      newpixel[x].b=(unsigned char)((float)pixel[x].b*currentBrightness);
    }
    data = (unsigned char *)newpixel;
  }
  sreg_prev=SREG;
  cli();  
  while (datlen--) {
    curbyte = *data++;
    asm volatile(
    "       ldi   %0,8  \n\t"
    "loop%=:            \n\t"
    "       out   %2,%3 \n\t"    //  '1' [01] '0' [01] - re
#if (w1_nops&1)
    w_nop1
#endif
#if (w1_nops&2)
    w_nop2
#endif
#if (w1_nops&4)
    w_nop4
#endif
#if (w1_nops&8)
    w_nop8
#endif
#if (w1_nops&16)
    w_nop16
#endif
    "       sbrs  %1,7  \n\t"    //  '1' [03] '0' [02]
    "       out   %2,%4 \n\t"    //  '1' [--] '0' [03] - fe-low
    "       lsl   %1    \n\t"    //  '1' [04] '0' [04]
#if (w2_nops&1)
    w_nop1
#endif
#if (w2_nops&2)
    w_nop2
#endif
#if (w2_nops&4)
    w_nop4
#endif
#if (w2_nops&8)
    w_nop8
#endif
#if (w2_nops&16)
    w_nop16 
#endif
    "       out   %2,%4 \n\t"    //  '1' [+1] '0' [+1] - fe-high
#if (w3_nops&1)
    w_nop1
#endif
#if (w3_nops&2)
    w_nop2
#endif
#if (w3_nops&4)
    w_nop4
#endif
#if (w3_nops&8)
    w_nop8
#endif
#if (w3_nops&16)
    w_nop16
#endif
    "       dec   %0    \n\t"    //  '1' [+2] '0' [+2]
    "       brne  loop%=\n\t"    //  '1' [+3] '0' [+4]
    :  "=&d" (ctr)
    :  "r" (curbyte), "I" (_SFR_IO_ADDR(ws2812b_PORTREG)), "r" (maskhi), "r" (masklo)
    );
  }
  SREG=sreg_prev;
}
