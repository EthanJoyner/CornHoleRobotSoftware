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

void setup() 
{
  Serial.begin(9600);
  Serial.setTimeout(50);
  pinMode(LED_BUILTIN, OUTPUT);
  
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
    
     //Do something with the data - like print it
//      Serial.print("Code: ");
//      Serial.println(dataIn);
//    
//      Serial.print("Type: ");
//      Serial.println(signalType);
//      
//      Serial.print("AL: ");
//      Serial.println(analogLeft);
//      
//      Serial.print("AR: ");
//      Serial.println(analogRight);
//      
//      Serial.print("AU: ");
//      Serial.println(armUp);
//      
//      Serial.print("AD: ");
//      Serial.println(armDown);
//      
//      Serial.print("Fire1: ");
//      Serial.println(fire1);
//      
//      Serial.print("Fire2: ");
//      Serial.println(fire2); 
      
      } else if (dataIn.substring(0,1).toInt() == 2){
  
        //Do something with the data - like print it
        Serial.print("Code: ");
        Serial.println(dataIn);
          
        signalType = dataIn.substring(0,1).toInt();
        moveType = dataIn.substring(1,2).toInt();
        moveTime = dataIn.substring(2,6).toInt();
  
//        Serial.print("Type: ");
//        Serial.println(signalType); 
//  
//        Serial.print("Movetype: ");
//        Serial.println(moveType); 
  
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
            
          // Default
          default:
//            Serial.println("Invalid Movement Code");
            break;
          }
        
//        Serial.print("Time: ");
//        Serial.println(moveTime); 
       
        
        } else {
//          Serial.println("No Signal...");
          //Do something with the data - like print it
//          Serial.print("Code: ");
//          Serial.println(dataIn);
          
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
