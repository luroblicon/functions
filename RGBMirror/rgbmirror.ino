// This #include statement was automatically added by the Particle IDE.
#include "PCA9534.h"
//Constructor of class object that controls the Expander
PCA9534 gpio;

//Pins connected to the expander that control the RGB
uint8_t rRGB = 7; //
uint8_t bRGB = 5;//
uint8_t gRGB = 6;//

//variable to store the brightness of the RGB
uint8_t ledBrightness;
uint8_t dutyCycle;


void setup() {
  gpio.begin();    
  gpio.pinMode(rRGB,OUTPUT);
  gpio.pinMode(bRGB,OUTPUT);
  gpio.pinMode(gRGB,OUTPUT);
  RGB.onChange(ledChangeHandler);

}

void loop() {
    
    RGB.onChange(ledChangeHandler);

}


void ledChangeHandler(uint8_t r, uint8_t g, uint8_t b){
  gpio.digitalWrite(rRGB,r);
  gpio.digitalWrite(bRGB,b);
  gpio.digitalWrite(gRGB,g);
}