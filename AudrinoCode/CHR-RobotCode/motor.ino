// Download Libary in the ArduinoLibs Folder
#include <RobojaxBTS7960.h>

// Front Left (Motor 1)
#define FL_RPWM 12  // define pin 3 for RPWM pin (output)
#define FL_R_EN 23  // define pin 2 for R_EN pin (input)
#define FL_R_IS 22  // define pin 5 for R_IS pin (output)
#define FL_LPWM 11  // define pin 6 for LPWM pin (output)
#define FL_L_EN 25  // define pin 7 for L_EN pin (input)
#define FL_L_IS 24  // define pin 8 for L_IS pin (output)

// Front Right (Motor 2)
#define FR_RPWM 10  // define pin 3 for RPWM pin (output)
#define FR_R_EN 27  // define pin 2 for R_EN pin (input)
#define FR_R_IS 26  // define pin 5 for R_IS pin (output)
#define FR_LPWM 9   // define pin 6 for LPWM pin (output)
#define FR_L_EN 29  // define pin 7 for L_EN pin (input)
#define FR_L_IS 28  // define pin 8 for L_IS pin (output)

// Back Left (Motor 3)
#define BL_RPWM 8   // define pin 3 for RPWM pin (output)
#define BL_R_EN 31  // define pin 2 for R_EN pin (input)
#define BL_R_IS 30  // define pin 5 for R_IS pin (output)
#define BL_LPWM 7   // define pin 6 for LPWM pin (output)
#define BL_L_EN 33  // define pin 7 for L_EN pin (input)
#define BL_L_IS 32  // define pin 8 for L_IS pin (output)

// Back Right (Motor 4)
#define BR_RPWM 6   // define pin 3 for RPWM pin (output)
#define BR_R_EN 35  // define pin 2 for R_EN pin (input)
#define BR_R_IS 34  // define pin 5 for R_IS pin (output)
#define BR_LPWM 5   // define pin 6 for LPWM pin (output)
#define BR_L_EN 37  // define pin 7 for L_EN pin (input)
#define BR_L_IS 36  // define pin 8 for L_IS pin (output)

// Providing variables for clockwise and couter-clockwise
#define CW 1
#define CCW 0

// If you want to debug
#define debug 1
#define noDebug 0

double motorSensitivity = 0.01;


// R_EN, R_PWM, R_IS, L_EN, L_PWM, L_IS, dubug?
RobojaxBTS7960 flM1(FL_R_EN, FL_RPWM, FL_R_IS, FL_L_EN, FL_LPWM, FL_L_IS, noDebug);  //define motor 1 object
RobojaxBTS7960 frM2(FR_R_EN, FR_RPWM, FR_R_IS, FR_L_EN, FR_LPWM, FR_L_IS, noDebug);  //define motor 2 object
RobojaxBTS7960 blM3(BL_R_EN, BL_RPWM, BL_R_IS, BL_L_EN, BL_LPWM, BL_L_IS, noDebug);  //define motor 3 object
RobojaxBTS7960 brM4(BR_R_EN, BR_RPWM, BR_R_IS, BR_L_EN, BR_LPWM, BR_L_IS, noDebug);  //define motor 4 object

bool initMotorContollers() {
  flM1.begin();
  ledDb(6);
  delay(100);
  frM2.begin();
  ledOrange(6);
  delay(100);
  blM3.begin();
  ledLb(6);
  delay(100);
  brM4.begin();
  ledPink(6);
  flM1.rotate(100,CW);
  delay(1000);
  frM2.rotate(100,CW);
  delay(1000);
  blM3.rotate(100,CW);
  delay(1000);
  brM4.rotate(100,CW);
  delay(1000);
  return true;
}

void motorFunction(int inputL, int inputR) {
  int inputIntL = inputL;
  int inputIntR = inputR;
  int currentSpeedL = 0;
  int currentSpeedR = 0;

  // Left Motors
  if (inputIntL > 50) {
    // Forward
    currentSpeedL = (inputIntL * motorSensitivity) + 50;
    flM1.rotate(currentSpeedL, CW);
    blM3.rotate(currentSpeedL, CW);
    delay(10);

  } else if (inputIntL < 50) {
    // Backward
    currentSpeedL = (inputIntL * motorSensitivity) + 50;
    flM1.rotate(currentSpeedL, CCW);
    blM3.rotate(currentSpeedL, CCW);
    delay(10);

  } else if (inputIntL == 50) {
    flM1.stop();
    blM3.stop();
    delay(10);

  } else if (inputIntL == 99) {
    flM1.rotate(100, CW);
    blM3.rotate(100, CW);
    delay(10);
  }

  // Right Motors
  if (inputIntR > 50) {
    // Forward
    currentSpeedR = (inputIntR * motorSensitivity) + 50;
    frM2.rotate(currentSpeedR, CCW);
    brM4.rotate(currentSpeedR, CCW);
    delay(10);

  } else if (inputIntR < 50) {
    // Backward
    currentSpeedR = (inputIntR * motorSensitivity) + 50;
    frM2.rotate(currentSpeedR, CW);
    brM4.rotate(currentSpeedR, CW);
    delay(10);

  } else if (inputIntR == 50) {
    frM2.stop();
    brM4.stop();
    delay(10);

  } else if (inputIntR == 99) {
    frM2.rotate(100, CW);
    brM4.rotate(100, CW);
    delay(10);
  }
}
