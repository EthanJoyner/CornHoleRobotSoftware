// Cornhole Robot Arduino Software (1.0.0)
// Includes
// Definitions
// Functions
// Setup
// Loop

// Includes
#include <Wire.h>

// Download Libary in the ArduinoLibs Folder
#include <RobojaxBTS7960.h>

// Downonad the jarzebski MPU6050 library on github 
#include <MPU6050.h>


// Definitions

// Start Motor Definitions (See ADR Wire Pinout Table for Confimatation)
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

// Back Left (Motor 3)
#define BL_RPWM 8 // define pin 3 for RPWM pin (output)
#define BL_R_EN 31 // define pin 2 for R_EN pin (input)
#define BL_R_IS 30 // define pin 5 for R_IS pin (output)
#define BL_LPWM 7 // define pin 6 for LPWM pin (output)
#define BL_L_EN 33 // define pin 7 for L_EN pin (input)
#define BL_L_IS 32 // define pin 8 for L_IS pin (output)

// Back Right (Motor 4)
#define BR_RPWM 6 // define pin 3 for RPWM pin (output)
#define BR_R_EN 35 // define pin 2 for R_EN pin (input)
#define BR_R_IS 34 // define pin 5 for R_IS pin (output)
#define BR_LPWM 5 // define pin 6 for LPWM pin (output)
#define BR_L_EN 37 // define pin 7 for L_EN pin (input)
#define BR_L_IS 36 // define pin 8 for L_IS pin (output)

// Providing variables for clockwise and couter-clockwise
#define CW 1 //
#define CCW 0 //

// If you want to debun 
#define debug 1
#define noDebug 0

// Analog Sensor Pins
#define robotVoltage A0
#define robotPSI A1
#define robotTemp A2

// Digital Pins
#define piezo 2
#define linAct 3
#define valve 38
#define compressor 39




// Sensor Values
int roboVolt, roboPsi, roboTemp = 0;

// Timers
// unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch, roll, yaw = 0;

// Controller Variables
int signalType, analogLeft, analogRight, armUp, armDown, playerFireReady, adminFireReady, targetPSI;

//Seq Variables
int moveType, moveTime, compressorRelay, valveRelay;


// R_EN, R_PWM, R_IS, L_EN, L_PWM, L_IS, dubug?
RobojaxBTS7960 flM1(FL_R_EN, FL_RPWM, FL_R_IS, FL_L_EN, FL_LPWM, FL_L_IS, noDebug);//define motor 1 object
RobojaxBTS7960 frM2(FR_R_EN, FR_RPWM, FR_R_IS, FR_L_EN, FR_LPWM, FR_L_IS, noDebug);//define motor 2 object
RobojaxBTS7960 blM3(BL_R_EN, BL_RPWM, BL_R_IS, BL_L_EN, BL_LPWM, BL_L_IS, noDebug);//define motor 3 object
RobojaxBTS7960 brM4(BR_R_EN, BR_RPWM, BR_R_IS, BR_L_EN, BR_LPWM, BR_L_IS, noDebug);//define motor 4 object


MPU6050 mpu;




// Motor Function takes an intervalue on a given axis an
void motorFunction(int input){
  int inputInt = input;
  int currentSpeed = 0;
  if (inputInt > 50){
    // Forward
    currentSpeed = (inputInt * 0.5) + 50;
    flM1.rotate(currentSpeed,CW);
    delay(10);
    
  } else if (inputInt < 50){
    // Backward
    currentSpeed = (inputInt * -0.5) + 50;
    flM1.rotate(currentSpeed,CCW);
    delay(10);
    
  } else if (inputInt == 50){
    flM1.stop();
    delay(10);
  
  } else if (inputInt == 99){
      flM1.rotate(100,CW);
      delay(10);

     }
  }



void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.setTimeout(50);
  Serial1.setTimeout(50);
  // pinMode(LED_BUILTIN, OUTPUT);
  pinMode(compressor, OUTPUT);
  pinMode(valve, OUTPUT);
  pinMode(robotPSI, INPUT);
  pinMode(robotTemp,INPUT);
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
  flM1.begin();
}

void loop()
{      
// Start data take in
while (Serial.available() > 0){
  // Read Bluetooth Status
  if (Serial1.available() > 0){
    int btControlStatus = Serial1.readString().toInt();
    if (btControlStatus == 1){
      // Serial.println("Admin is Ready to Fire!");
      adminFireReady = 1;
    } else {
      // Serial.println("Signal Recived but not ready to fire");
      adminFireReady = 0;
    }
  }

    String dataIn = Serial.readString();
  
    if (dataIn.substring(0,1).toInt() == 1){
  
      signalType = dataIn.substring(0,1).toInt();
      analogLeft = dataIn.substring(1,3).toInt();
      analogRight = dataIn.substring(3,5).toInt();
      armUp = dataIn.substring(5,6).toInt();
      armDown = dataIn.substring(6,7).toInt();
      playerFireReady = dataIn.substring(7,8).toInt();
      
      if (dataIn.substring(8,11) == "und"){
        targetPSI = 0;
      } else {
        targetPSI = dataIn.substring(8,11).toInt();
      }
      

      motorFunction(analogLeft);
      motorFunction(analogRight); 
   
    if(playerFireReady == 1 && adminFireReady == 1){
        digitalWrite(valve,HIGH);
      }
       else{
        digitalWrite(valve,LOW);

      }

//      If a type 2 command (sequence Command)
      }else if (dataIn.substring(0,1).toInt() == 2){
  
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

    // Robot Voltage
    int voltValue = analogRead(robotVoltage);
    float voltage = voltValue * (5.0/1024.0);

    // Robot PSI
    int psiValue = analogRead(robotPSI);
    float psi = psiValue * (5.0/1024.0);

    // Robot Tempature
    int tempValue = analogRead(robotTemp);
    float tempature = tempValue * (5.0/1024.0);


    //  Serial.print ("Voltage lvl = ");
    
    // timer = millis();
  
    // Read normalized values
    Vector norm = mpu.readNormalizeGyro();
  
    // Calculate Pitch, Roll and Yaw
    pitch = pitch + norm.YAxis * timeStep;
    roll = roll + norm.XAxis * timeStep;
    yaw = yaw + norm.ZAxis * timeStep;
  
    String sensorCode = String(voltage)+ ", " + String(pitch) + ", " + String(roll) + ", " + String(yaw) + ", " + String(psi) + ", " + String(tempature);
    Serial.println(sensorCode);
    // Wait to full timeStep period
    //delay((timeStep*1000) - (millis() - timer));
    delay(50);
  
  }
    
}
