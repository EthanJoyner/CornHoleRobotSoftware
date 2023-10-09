#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        11 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 7 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAY 500

int incomingByte = 0; // for incoming serial data

void setup() {
  // put your setup code here, to run once:
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  pixels.clear(); //makes sure that we start off on a blank strip


  //pixels.setPixelColor( place on led strip, sets up the color in ( r, g , b));
  //pixels.setPixelColor(0, pixels.Color(0, 150, 0));// pixel 1
  //pixels.setPixelColor(1, pixels.Color(0, 150, 0));// pixel 2
  //pixels.setPixelColor(2, pixels.Color(0, 150, 0));// pixel 3
  //pixels.setPixelColor(3, pixels.Color(0, 150, 0));// pixel 4
  //pixels.setPixelColor(4, pixels.Color(0, 150, 0));// pixel 5
  //pixels.setPixelColor(5, pixels.Color(0, 150, 0));// pixel 6
  //pixels.setPixelColor(6, pixels.Color(0, 150, 0));// pixel 7
  
  pixels.show(); // Send the updated pixel colors to the hardware.
  delay(DELAY); // half second pause before starts again

  for (int i = 0; i<=6; i++)  {
    // send data only when you receive data:
    if (Serial.available()) {
      // read the incoming byte:
      incomingByte = Serial.readString();
      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte, DEC);
      if (incomingByte == 1) {
        
        }
      }
    }
}
