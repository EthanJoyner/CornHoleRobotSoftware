// Download Libary in the ArduinoLibs Folder
#include <RobojaxBTS7960.h>

// Front Left (Motor 1)
#define FL_RPWM 12 // define pin 3 for RPWM pin (output)
#define FL_R_EN 23 // define pin 2 for R_EN pin (input)
#define FL_R_IS 22 // define pin 5 for R_IS pin (output)
#define FL_LPWM 11 // define pin 6 for LPWM pin (output)
#define FL_L_EN 25 // define pin 7 for L_EN pin (input)
#define FL_L_IS 24 // define pin 8 for L_IS pin (output)

// Front Right (Motor 2)
#define FR_RPWM 10 // define pin 3 for RPWM pin (output)
#define FR_R_EN 27 // define pin 2 for R_EN pin (input)
#define FR_R_IS 26 // define pin 5 for R_IS pin (output)
#define FR_LPWM 9 // define pin 6 for LPWM pin (output)
#define FR_L_EN 29 // define pin 7 for L_EN pin (input)
#define FR_L_IS 28 // define pin 8 for L_IS pin (output)

// Providing variables for clockwise and couter-clockwise
#define CW 1 
#define CCW 0 

// If you want to debug
#define debug 1
#define noDebug 0

// Controller Variables
int signalType, analogLeft, analogRight, armUp, armDown, playerFireReady, adminFireReady, targetPSI;
double motorSensitivity = 0.01;

// R_EN, R_PWM, R_IS, L_EN, L_PWM, L_IS, dubug?
RobojaxBTS7960 flM1(FL_R_EN, FL_RPWM, FL_R_IS, FL_L_EN, FL_LPWM, FL_L_IS, noDebug);//define motor 1 object
RobojaxBTS7960 frM2(FR_R_EN, FR_RPWM, FR_R_IS, FR_L_EN, FR_LPWM, FR_L_IS, noDebug);//define motor 2 object

// Motor Function takes an intervalue on a given axis an
void motorFunction(int inputL, int inputR){
  int inputIntL = inputL;
  int inputIntR = inputR;
  int currentSpeedL = 0;
  int currentSpeedR = 0;
  
  // Left Motors  
  if (inputIntL > 50 ){
    // Forward
    currentSpeedL = (inputIntL);
    flM1.rotate(currentSpeedL,CW);
    delay(10);
    
  } else if (inputIntL < 50){
    // Backward
    currentSpeedL = (inputIntL);
    flM1.rotate(currentSpeedL,CCW);
    delay(10);
    
  } else if (inputIntL == 50){
    flM1.stop();
    delay(10);
  
  } else if (inputIntL == 99){
      flM1.rotate(100,CW);
      delay(10);
      }

// Right Motors
    if (inputIntR > 50 ){
        // Forward
        currentSpeedR = (inputIntR);
        frM2.rotate(currentSpeedR,CCW);
        delay(10);
        
      } else if (inputIntR < 50){
        // Backward
        currentSpeedR = (inputIntR);
        frM2.rotate(currentSpeedR,CW);
        delay(10);
        
      } else if (inputIntR == 50){
        frM2.stop();
        delay(10);
      
      } else if (inputIntR == 99){
          frM2.rotate(100,CW);
          delay(10);
     }
 }

void setup(void) 
{  
  // Set up Serial Channels
  Serial.begin(9600);
  Serial.setTimeout(50);
  
// Initilize Motors
  flM1.begin();
  delay(100);
  frM2.begin();
}

void loop()
{      
// Start data take in
while (Serial.available() > 0){
    String dataIn = Serial.readString();
    if (dataIn.substring(0,1).toInt() == 1){
      analogLeft = dataIn.substring(1,3).toInt();
      analogRight = dataIn.substring(3,5).toInt();
      motorFunction(analogLeft, analogRight);
      Serial.println("Left: " + String(analogLeft));
      Serial.println("Right: " + String(analogRight));
      

  } 
    delay(50);
  }
}