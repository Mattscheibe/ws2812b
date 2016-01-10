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
* Edit this file for setting up data output pin and wiring scheme.
*/
#ifndef ws2812b_config_h_
#define ws2812b_config_h_
///////////////////////// E D I T  Y O U R   S E T T I N G S  H E R E: ////////////////////////////////
// Data connection pin:                                                                               //
#define ws2812b_Port  B                                                                               //
#define ws2812b_Pin   4                                                                               //
// Wiring scheme:                                                                                     //
#define WIDTH  3  // for single strands (no matrix) set to length of strand (or to 2 for single LED)  //
#define HEIGHT 1  // for single strands (no matrix) set to 1                                         //
#define TYPE   1  // for single strands (no matrix) set to 1                                        //
                                                                                                   //
/*                          o            o             ^         o           o                    //
                   Type  0: ||_||¯||  1: ||/||/||   2: ||_||¯||_|| 3: ||\||\||                   //
                                   v            v                     v                         //
                                                                                               //
                   Type  4: o=      5: o=       6: =o       7: =o                             //
                              |         /         |            \                             //
                             =          =          =           =                            //
                            |           /           |          \                           //
                             =>         =>        <=          <=                          //
                                                                                         //
                                 ^             ^      ^              ^                  //
                Type  8:  ||¯||_||  9: ||\||\||  10: ||_||¯||  11: ||/||/||            //
                          o            o                    o             o           //
                                                                                     //
                Type 12:  =>    13:  =>      14:<=      15:<=                       //
                         |           \            |          /                     //
                          =          =           =           =                    //
                           |         \          |            /                   //
                         o=         o=           =o          =o                 //
                                                                               //
            ( double lines symbolize strands, single lines interconnections ) //                                                                                     //
                                                                             //
            ( o mark positions of input to strand = Din )                   //
                                                                           //
            ( arrows indicate strand's direction => towards Dout )        //
                                                                         //
            ( schemes are illustrated with 3 or 4 elements, yet parts   //
              of strands may actually be of any length and number)     // 
                                                                      //
*//////////////////////////////////////////////////////////////////////
#endif
