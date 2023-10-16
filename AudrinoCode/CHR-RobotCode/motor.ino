// Download Libary in the ArduinoLibs Folder
#include <RobojaxBTS7960.h>

// Left Motors
#define L_RPWM 12  // define pin 3 for RPWM pin (output)
#define L_R_EN 23  // define pin 2 for R_EN pin (input)
#define L_R_IS 22  // define pin 5 for R_IS pin (output)
#define L_LPWM 11  // define pin 6 for LPWM pin (output)
#define L_L_EN 25  // define pin 7 for L_EN pin (input)
#define L_L_IS 24  // define pin 8 for L_IS pin (output)

// Right Motors
#define R_RPWM 10  // define pin 3 for RPWM pin (output)
#define R_R_EN 27  // define pin 2 for R_EN pin (input)
#define R_R_IS 26  // define pin 5 for R_IS pin (output)
#define R_R_IS 9   // define pin 6 for LPWM pin (output)
#define R_L_EN 29  // define pin 7 for L_EN pin (input)
#define R_L_IS 28  // define pin 8 for L_IS pin (output)

// Providing variables for clockwise and couter-clockwise
#define CW 1
#define CCW 0

// If you want to debug
#define debug 1
#define noDebug 0

double motorSensitivity = 0.01;


// R_EN, R_PWM, R_IS, L_EN, L_PWM, L_IS, dubug?
RobojaxBTS7960 leftMotors(L_R_EN, L_RPWM, L_R_IS, L_L_EN, L_LPWM, L_L_IS, noDebug);  //define motor 1 object
RobojaxBTS7960 rightMotors(R_R_EN, R_RPWM, R_R_IS, R_L_EN, R_R_IS, R_L_IS, noDebug);  //define motor 2 object

bool initMotorContollers() {
  leftMotors.begin();
  ledDb(6);
  delay(100);
  rightMotors.begin();
  ledOrange(6); 
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
    // currentSpeedL = (inputIntL * motorSensitivity) + 50;
    currentSpeedL = (inputIntL);
    Serial.println("Left: " + String(currentSpeedL));
    leftMotors.rotate(currentSpeedL, CW);
    delay(10);

  } else if (inputIntL < 50) {
    // Backward
    // currentSpeedL = (inputIntL * motorSensitivity) + 50;
    currentSpeedL = (inputIntL);
    Serial.println("Left: " + String(currentSpeedL));
    leftMotors.rotate(currentSpeedL, CCW);
    delay(10);

  } else if (inputIntL == 50) {
    Serial.println("Left Stop");
    leftMotors.stop();
    delay(10);

  } else if (inputIntL == 99) {
    Serial.println("Left Max");
    leftMotors.rotate(100, CW);
    delay(10);
  }

  // Right Motors
  if (inputIntR > 50) {
    // Forward
    // currentSpeedR = (inputIntR * motorSensitivity) + 50;
    currentSpeedR = (inputIntR);
    Serial.println("Right: " + String(currentSpeedR));
    rightMotors.rotate(currentSpeedR, CCW);
    delay(10);

  } else if (inputIntR < 50) {
    // Backward
    // currentSpeedR = (inputIntR * motorSensitivity) + 50;
    currentSpeedR = (inputIntR);
    Serial.println("Right: " + String(currentSpeedR));
    rightMotors.rotate(currentSpeedR, CW);
    delay(10);

  } else if (inputIntR == 50) {
    Serial.println("Right Stop");
    rightMotors.stop();
    delay(10);

  } else if (inputIntR == 99) {
    Serial.println("Right Max");
    rightMotors.rotate(100, CW);
    delay(10);
  }
}
