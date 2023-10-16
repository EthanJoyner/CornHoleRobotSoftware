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

// Download the jarzebski MPU6050 library on github 
#include <MPU6050.h>

// Download DallasTempature 
#include <OneWire.h>
#include <DallasTemperature.h>

// Leds
#include <Adafruit_NeoPixel.h>

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
#define CW 1 
#define CCW 0 

// If you want to debug
#define debug 1
#define noDebug 0

// Analog Sensor Pins
#define robotVoltage A0
#define robotPSI 52
#define robotTemp 4

// Digital Pins
#define piezo 2
#define linAct 3
#define valve 38
#define compressor 39

// Leds 
#define led 51
#define ledCount 7

// Sensor Values
float roboVolt, roboPsi, roboTemp = 0;

// Tempature Constants
const int pressureInput = A0; //select the analog input pin for the pressure transducer
const int pressureZero = 102.4; //analog reading of pressure transducer at 0psi
const int pressureMax = 921.6; //analog reading of pressure transducer at 100psi
const int pressuretransducermaxPSI = 100; //psi value of transducer being used
const int sensorreadDelay = 250; //constant integer to set the sensor read delay in milliseconds

// Timers
// unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch, roll, yaw = 0;

// Controller Variables
int signalType, analogLeft, analogRight, armUp, armDown, playerFireReady, adminFireReady, targetPSI;
double motorSensitivity = 0.01;
//Seq Variables
int moveType, moveTime, compressorRelay, valveRelay;


// R_EN, R_PWM, R_IS, L_EN, L_PWM, L_IS, dubug?
RobojaxBTS7960 flM1(FL_R_EN, FL_RPWM, FL_R_IS, FL_L_EN, FL_LPWM, FL_L_IS, noDebug);//define motor 1 object
RobojaxBTS7960 frM2(FR_R_EN, FR_RPWM, FR_R_IS, FR_L_EN, FR_LPWM, FR_L_IS, noDebug);//define motor 2 object
RobojaxBTS7960 blM3(BL_R_EN, BL_RPWM, BL_R_IS, BL_L_EN, BL_LPWM, BL_L_IS, noDebug);//define motor 3 object
RobojaxBTS7960 brM4(BR_R_EN, BR_RPWM, BR_R_IS, BR_L_EN, BR_LPWM, BR_L_IS, noDebug);//define motor 4 object

MPU6050 mpu;

OneWire oneWire(robotTemp);
DallasTemperature sensors(&oneWire);

// Motor Function takes an intervalue on a given axis an
void motorFunction(int inputL, int inputR){
  int inputIntL = inputL;
  int inputIntR = inputR;
  int currentSpeedL = 0;
  int currentSpeedR = 0;
  
  // Left Motors  
  if (inputIntL > 50 ){
    // Forward
    currentSpeedL = (inputIntL * motorSensitivity) + 50;
    flM1.rotate(currentSpeedL,CW);
    delay(10);
    
  } else if (inputIntL < 50){
    // Backward
    currentSpeedL = (inputIntL * motorSensitivity) + 50;
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
        currentSpeedR = (inputIntR * motorSensitivity) + 50;
        frM2.rotate(currentSpeedR,CCW);
        delay(10);
        
      } else if (inputIntR < 50){
        // Backward
        currentSpeedR = (inputIntR * motorSensitivity) + 50;
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
  // LEDs Starts
  Adafruit_NeoPixel strip(ledCount, led, NEO_GRB + NEO_KHZ800);


  // Configure Relay and Sensors
  pinMode(compressor, OUTPUT);
  pinMode(valve, OUTPUT);
  pinMode(robotPSI, INPUT);
  pinMode(robotTemp,INPUT);
  pinMode(piezo, OUTPUT);
  
  // Set up Serial Channels
  Serial.begin(9600);
  Serial1.begin(9600);
  // Set Respnse time to 50ms
  Serial.setTimeout(50);
  Serial1.setTimeout(50);

  // Configure Bluetooth Module {Needs work}

  
// Initilize Motors
  flM1.begin();
  delay(100);
  frM2.begin();
  delay(100);
  blM3.begin();
  delay(100);
  brM4.begin();
  delay(100);

// Check Tempature sensor
  sensors.begin();
// Check PSI Sensor
  roboPsi = analogRead(robotPSI); //reads value from input pin and assigns to variable
  roboPsi = ((roboPsi-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero); //conversion equation to convert analog reading to psi

// Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();
  mpu.setThreshold(3);
  
 
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
      // Serial.println("Signal type: " + String(signalType));
      analogLeft = dataIn.substring(1,3).toInt();
      // Serial.println("Analog Left: " + String(analogLeft));
      analogRight = dataIn.substring(3,5).toInt();
      //  Serial.println("Analog Right: " + String(analogRight));
      armUp = dataIn.substring(5,6).toInt();
      // Serial.println("Arm Up: " + String(armUp));
      armDown = dataIn.substring(6,7).toInt();
      // Serial.println("Arm Down: " + String(armDown));
      playerFireReady = dataIn.substring(7,8).toInt();
      // Serial.println("Fire: " + String(playerFireReady));

      // Serial.println(dataIn.substring(8,11) + " , " + String(dataIn.substring(8,11).toInt()) );

      if (dataIn.substring(8,11) == "und"){
        targetPSI = 0;
      } else {
        targetPSI = dataIn.substring(8,11).toInt();
      }

      motorFunction(analogLeft, analogRight); 
   
    if(playerFireReady == 1 && adminFireReady == 1){
        digitalWrite(valve,LOW);
      }
       else{
        digitalWrite(valve,HIGH);

      }

      // Serial.println(String(analogRead(robotPSI)*(5.0/1024.0)));
      // Serial.println(analogRead(robotPSI));
    roboPsi = analogRead(robotPSI); //reads value from input pin and assigns to variable
    roboPsi = ((roboPsi-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero);
    if (roboPsi  < targetPSI){
      // Serial.println("Current Psi is lower than target");
      // Serial.println(analogRead(robotPSI));
      digitalWrite(compressor, LOW);
      // Serial.println(analogRead(robotPSI));
    } else {
      digitalWrite (compressor, HIGH);
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
    roboPsi = analogRead(robotPSI); //reads value from input pin and assigns to variable
    roboPsi = ((roboPsi-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero); //conversion equation to convert analog reading to psi
   
    // Robot Tempature
    roboTemp = sensors.getTempFByIndex(0); // Use a simple function to print out the data
  
    // Read normalized values
    Vector norm = mpu.readNormalizeGyro();
  
    // Calculate Pitch, Roll and Yaw
    pitch = pitch + norm.YAxis * timeStep;
    roll = roll + norm.XAxis * timeStep;
    yaw = yaw + norm.ZAxis * timeStep;
  
    String sensorCode = String(voltage)+ ", " + String(pitch) + ", " + String(roll) + ", " + String(yaw) + ", " + String(roboPsi) + ", " + String(roboTemp);
    Serial.println(sensorCode);
    // Wait to full timeStep period
    //delay((timeStep*1000) - (millis() - timer));
    delay(50);
  
  }
    
}