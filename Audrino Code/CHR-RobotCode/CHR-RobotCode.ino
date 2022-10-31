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


#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

// Controller Variables
int signalType;
int analogLeft;
int analogRight;
int armUp;
int armDown;
int fire1;
int fire2;

//Seq Variables
int moveType;
int moveTime; 
int compressorRelay = 7;
int valveRelay = 13;

void motorFunction(int input){
  int inputInt = input;
  int currentSpeed = 0;
  if (inputInt > 50){
    // Forward
    currentSpeed = (inputInt * 0.5) + 50;
    motor1.rotate(currentSpeed,CW);
    delay(10);
    
  } else if (inputInt < 50){
    // Backward
    currentSpeed = (inputInt * -0.5) + 50;
    motor1.rotate(currentSpeed,CCW);
    delay(10);
    
  } else if (inputInt == 50){
    motor1.stop();
    delay(10);
  
  } else if (inputInt == 99){
      motor1.rotate(100,CW);
      delay(10);

     }
  }

void setup() 
{
  Serial.begin(9600);
  Serial.setTimeout(50);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(compressorRelay, OUTPUT);
  pinMode(valveRelay, OUTPUT);
  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
  motor1.begin();
}

void loop()
{      
// Start data take in
while (Serial.available() > 0){
      
    String dataIn = Serial.readString();
  
  
    if (dataIn.substring(0,1).toInt() == 1){
  
      signalType = dataIn.substring(0,1).toInt();
      analogLeft = dataIn.substring(1,3).toInt();
      analogRight = dataIn.substring(3,5).toInt();
      armUp = dataIn.substring(5,6).toInt();
      armDown = dataIn.substring(6,7).toInt();
      fire1 = dataIn.substring(7,8).toInt();
      fire2 = dataIn.substring(8,9).toInt();

      motorFunction(analogLeft); 
   
    if(fire1 == 1 && fire2 == 1){
        digitalWrite(valveRelay, HIGH);
      }
      else{
        digitalWrite(valveRelay, LOW);
      }

//      If a type 2 command (sequence Command)
    } else if (dataIn.substring(0,1).toInt() == 2){
  
        //Do something with the data - like print it
        Serial.print("Code: ");
        Serial.println(dataIn);
          
        signalType = dataIn.substring(0,1).toInt();
        moveType = dataIn.substring(1,2).toInt();
        moveTime = dataIn.substring(2,6).toInt();
  
  
        switch (moveType){
          // Move forward
          case 1:
//            Serial.println("Move Forward"); 
            break;
            
          // Move backward
          case 2:
//            Serial.println("Move Backwards");
            break; 
          
          // Turn left
          case 3:
//            Serial.println("Turn Left"); 
            break;
          
          // Turn right
          case 4:
//            Serial.println("Turn Right");
            break; 
          
          // Arm up
          case 5:
//            Serial.println("Arm Up");
            break; 
          
          // Arm down
          case 6:
//            Serial.println("Arm Down");
            break;

            // Compress to
          case 7:
//            Serial.println("compress to");
            break;
            
          // Default
          default:
//            Serial.println("Invalid Movement Code");
            break;
          }
       
        
        } else {
            // Serial.println("No Signal...");
            // Do something with the data - like print it
            // Serial.print("Code: ");
            // Serial.println(dataIn);
          }

    // Start data Send out
    Vector rawGyro = mpu.readRawGyro();
    Vector normGyro = mpu.readNormalizeGyro();
  
    int value = analogRead(A0);
    float voltage = value * (5.0/1024.0);
    //  Serial.print ("Voltage lvl = ");
    
    timer = millis();
  
    // Read normalized values
    Vector norm = mpu.readNormalizeGyro();
  
    // Calculate Pitch, Roll and Yaw
    pitch = pitch + norm.YAxis * timeStep;
    roll = roll + norm.XAxis * timeStep;
    yaw = yaw + norm.ZAxis * timeStep;
  
    String sensorCode = String(voltage)+ ", " + String(pitch) + ", " + String(roll) + ", " + String(yaw);
    Serial.println(sensorCode);
    // Wait to full timeStep period
    //delay((timeStep*1000) - (millis() - timer));
    delay(50);
  
  }
    
}
