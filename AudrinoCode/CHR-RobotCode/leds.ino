// Leds
#include <Adafruit_NeoPixel.h>

// Leds 
#define LED_PIN    53
#define LED_COUNT 7

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void initLeds(){
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.setPixelColor(3, pixels.Color(255, 255, 225));
  pixels.show();  
  piezoInspPass();
}

void ledPass(int idx){
  pixels.setPixelColor(idx, pixels.Color(0, 255, 0));
  pixels.show();
}

void ledFail(int idx){
  pixels.setPixelColor(idx, pixels.Color(255, 0, 0));
  pixels.show();
}

// Orange
void ledOrange(int idx){
  pixels.setPixelColor(idx, pixels.Color(252, 95, 43));
  pixels.show();
}
// Dark blue
void ledDb(int idx){
  pixels.setPixelColor(idx, pixels.Color(14, 41, 245));
  pixels.show();
}

// green
void ledGreen(int idx){
  pixels.setPixelColor(idx, pixels.Color(114, 242, 97));
  pixels.show();
}

// Light Blue
void ledLb(int idx){
  pixels.setPixelColor(idx, pixels.Color(69, 247, 221));
  pixels.show();
} 

// Pink
void ledPink(int idx){
  pixels.setPixelColor(idx, pixels.Color(230, 106, 194));
  pixels.show();
}