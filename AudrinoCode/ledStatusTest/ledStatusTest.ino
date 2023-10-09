#include <Adafruit_NeoPixel.h>
#define LED_PIN    53
#define LED_COUNT 7
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
  Serial.begin(9600);
  Serial.println("Ready...");
  pixels.setPixelColor(3, pixels.Color(255, 255, 225));
  pixels.show();  
  delay(1500);
}
void loop() {

  // M1, M2, M3, M4, Temp, Psi, BT1, AudioCheck, Gyro

  String input = "1111111";
  
// M1
  if (input[0] == '1'){
    pixels.setPixelColor(0, pixels.Color(0, 0, 225));
    pixels.show();  
    delay(1500);
   } else {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();  
    delay(1500);
  }
  
// M2
  if (input[1] == '1'){
    pixels.setPixelColor(0, pixels.Color(255, 0, 255));
    pixels.show();  
    delay(1500);
   } else {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();  
    delay(1500);
  }

// M3
  if (input[2] == '1'){
    pixels.setPixelColor(0, pixels.Color(255, 255, 0));
    pixels.show();  
    delay(1500);
   } else {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show(); 
    delay(1500);
  }

// M4
  if (input[3] == '1'){
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.show();  
    delay(1500);
   } else {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();  
    delay(1500);
  }
// Temp
  if (input[4] == '1'){
    pixels.setPixelColor(1, pixels.Color(0, 0, 255));
    pixels.show();  
    delay(1500);
   } else {
    pixels.setPixelColor(1, pixels.Color(255, 0, 0));
    pixels.show();  
    delay(1500);
  }
// PSI
  if (input[5] == '1'){
    pixels.setPixelColor(1, pixels.Color(0, 255, 0));
    pixels.show();  
    delay(1500);
   } else {
    pixels.setPixelColor(1, pixels.Color(255, 0, 0));
    pixels.show();  
    delay(1500);
  }

// BT
while( input[6] != 1){
  pixels.setPixelColor(2, pixels.Color(255, 0, 0));
  pixels.show();  
  delay(1500);
}
  pixels.setPixelColor(2, pixels.Color(0, 255, 0));
  pixels.show();  
  delay(1500);
  

  if (input[6] == '1'){
    pixels.setPixelColor(6, pixels.Color(0, 255, 0));
    pixels.show();  
    delay(1500);
   } else {
    pixels.setPixelColor(6, pixels.Color(255, 0, 0));
    pixels.show();  
    delay(1500);
  }



}

