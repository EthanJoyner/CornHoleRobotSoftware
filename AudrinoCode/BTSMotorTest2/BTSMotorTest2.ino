// pins for motor 1
#define RPWM_1 3 // define pin 3 for RPWM pin (output)
#define R_EN_1 4 // define pin 2 for R_EN pin (input)
#define R_IS_1 5 // define pin 5 for R_IS pin (output)

#define LPWM_1 6 // define pin 6 for LPWM pin (output)
#define L_EN_1 7 // define pin 7 for L_EN pin (input)
#define L_IS_1 8 // define pin 8 for L_IS pin (output)
// motor 1 pins end here


#define CW 1 //
#define CCW 0 //
#define debug 1 //

#include <RobojaxBTS7960.h>
RobojaxBTS7960 motor1(R_EN_1,RPWM_1,R_IS_1, L_EN_1,LPWM_1,L_IS_1,0);//define motor 1 object


void motorFunction(String input){
  int inputInt = input.toInt();
  int currentSpeed = 0;
  if (inputInt > 50){
    // Forward
    currentSpeed = (inputInt * 0.5) + 50;
    motor1.rotate(currentSpeed,CW);
    delay(100);
    
  } else if (inputInt < 50){
    // Backward
    currentSpeed = (inputInt * -0.5) + 50;
    motor1.rotate(currentSpeed,CCW);
    delay(100);
    
  } else if (inputInt == 50){
    motor1.stop();
    delay(100);
  
  } else if (inputInt == 99){
      motor1.rotate(100,CW);
      delay(100);

     }
  }


  void setup() {
  // BTS7960 Motor Control Code by Robojax.com 20190622
  Serial.begin(9600);// setup Serial Monitor to display information

   motor1.begin();   
    // BTS7960 Motor Control Code by Robojax.com 20190622 
}

void loop() {

  String inputIO = "00";

  motorFunction(inputIO); 


}// loop ends
