/*
Source code for RainbowCycle - Dale's First PCB
Controls 10 RGB LEDs with two TLC5940s and one ATMega328P-PU
Also has two potentiometers for manipulating brightness and speed of the color wheel

* Important: this code depends on the tlc5940arduino library. * 
http://code.google.com/p/tlc5940arduino/downloads/list
*/

#include "Tlc5940.h" // This is required, don't forget it :P

// Experimental "Faster Analog" Code
#define FASTADC 1
// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
// End Experimental "Faster Analog" Code

#define NUM_LEDS 10                   // number of RGB LEDs controlled

struct RGB { byte r; byte g; byte b; };
RGB rgb;

// Potentiometers 
const int brightness_pot_pin = A2;    // analog input pin that the brightness potentiometer is attached to
const int speed_pot_pin = A3;         // analog input pin that the speed potentiometer is attached to

int brightness_pot = 0;               // raw value read from brightness potentiometer
int brightness_mapped = 0;            // mapped value from brightness potentiometer
int speed_pot = 0;                    // raw value read from speed potentiometer
int speed_mapped = 0;                 // mapped value from speed potentiometer

void setup(){
  
// More Experimental "Faster Analog" Code
  #if FASTADC
  // set prescale to 16
  sbi(ADCSRA,ADPS2);
  cbi(ADCSRA,ADPS1);
  cbi(ADCSRA,ADPS0);
  #endif
// End Experimental "Faster Analog" Code
  Tlc.init();  
}

void loop(){

  randomSeed(millis());

  int dim=random(4,6);
  int max_cycles=0;
  int cycles=-1;

  rainbowCycle(speed_mapped,cycles,dim);

}

void setLed(byte num,int red,int green,int blue){

  if(brightness_mapped){
    red=red/brightness_mapped;
    green=green/brightness_mapped;
    blue=blue/brightness_mapped;
  }

  Tlc.set(num*3,red);
  Tlc.set(num*3+1,green);
  Tlc.set(num*3+2,blue);

} 

void rainbowCycle(uint8_t speed_mapped,byte cycle,byte dim) {

  int cycles, j, k;

  for(cycles=0;cycles<cycle;cycles++){

    byte dir=0;
    k=255;

    for (j=0; j < 256; j++,k--) {
      // read the "analog in" values:
      brightness_pot = analogRead(brightness_pot_pin);
      speed_pot = analogRead(speed_pot_pin);

      // map the readings to their appropriate ranges
      brightness_mapped = map(brightness_pot, 1, 1023, 1, 48);
      speed_mapped = map(speed_pot, 0, 1023, 0.1, 30);

      if(k<0)k=255;

      for(int i=0; i<NUM_LEDS; i+=1) {
        // read the "analog in" values:
        brightness_pot = analogRead(brightness_pot_pin);
        speed_pot = analogRead(speed_pot_pin);

        // map the readings to their appropriate ranges
        brightness_mapped = map(brightness_pot, 1, 1023, 1, 48);
        speed_mapped = map(speed_pot, 0, 1023, 0.1, 30);

        int brightness_mapped = brightness_mapped; 
        Wheel(((i * 256 / NUM_LEDS) + (dir==0?j:k)) % 256,dim);

        setLed(i,rgb.r*32,rgb.g*32,rgb.b*32);

      }
      Tlc.update();
      delay(speed_mapped);
    }
  }
}

void Wheel(byte WheelPos,byte dim){

  if (WheelPos < 85) {
    rgb.r=0;
    rgb.g=WheelPos * 3/dim;
    rgb.b=(255 - WheelPos * 3)/dim;;
    return;
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    rgb.r=WheelPos * 3/dim;
    rgb.g=(255 - WheelPos * 3)/dim;
    rgb.b=0;
    return;
  }
  else {
    WheelPos -= 170; 
    rgb.r=(255 - WheelPos * 3)/dim;
    rgb.g=0;
    rgb.b=WheelPos * 3/dim;
    return;
  }
}
