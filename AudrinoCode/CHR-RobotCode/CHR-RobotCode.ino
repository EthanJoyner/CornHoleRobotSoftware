// Cornhole Robot Arduino Software (2.0.0)
#define linAct 3


// Sensor Values
float roboVolt, roboPsi, roboTemp = 0;

// Controller Variables
int signalType, analogLeft, analogRight, armUp, armDown, playerFireReady, adminFireReady, targetPSI;

//Seq Variables
int moveType, moveTime, compressorRelay, valveRelay;

// Motor Function takes an intervalue on a given axis an

void setup() {
  initPiezo();
  piezoBoot();
  delay(1000);

  initLeds();
  delay(1000);

  if(initBluetooth()){
    ledPass(0);
  } else {
    ledFail(0);
  }
  delay(1000);

  if(initVolts()){
    ledPass(1);
  } else {
    ledFail(1);
  }
  delay(1000);
  
  if(initGryo()){
    ledPass(2);
  } else {
    ledFail(2);
  }
  delay(1000);
  
  if(initPsi()){
    ledPass(4);
  } else {
    ledFail(4);
  }
  delay(1000);
  
  if(initTemp()){
    ledPass(5);
  } else {
    ledFail(5);
  }
  delay(1000);

  if(initMotorContollers()){
    ledPass(6);
    piezoInspPass();
  } else {
    ledFail(6);
  }
  delay(1000);

}

void loop() {
  // Start data take in
  while (Serial.available() > 0) {
    // Read Bluetooth Status
    if (Serial1.available() > 0) {
      int btControlStatus = Serial1.readString().toInt();
      if (btControlStatus == 1) {
        // Serial.println("Admin is Ready to Fire!");
        adminFireReady = 1;
      } else {
        // Serial.println("Signal Recived but not ready to fire");
        adminFireReady = 0;
      }
    }

    String dataIn = Serial.readString();

    if (dataIn.substring(0, 1).toInt() == 1) {
      signalType = dataIn.substring(0, 1).toInt();
      analogLeft = dataIn.substring(1, 3).toInt();
      analogRight = dataIn.substring(3, 5).toInt();
      armUp = dataIn.substring(5, 6).toInt();
      armDown = dataIn.substring(6, 7).toInt();
      playerFireReady = dataIn.substring(7, 8).toInt();

      if (dataIn.substring(8, 11) == "und") {
        targetPSI = 0;
      } else {
        targetPSI = dataIn.substring(8, 11).toInt();
      }

      motorFunction(analogLeft, analogRight);
      shouldFire(playerFireReady, adminFireReady);

      //      If a type 2 command (sequence Command)
    } else if (dataIn.substring(0, 1).toInt() == 2) {

      //Do something with the data - like print it
      Serial.print("Code: ");
      Serial.println(dataIn);

      signalType = dataIn.substring(0, 1).toInt();
      moveType = dataIn.substring(1, 2).toInt();
      moveTime = dataIn.substring(2, 6).toInt();


      switch (moveType) {
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


    int voltage = 0;

    String sensorCode = String(voltage) + ", " + String(getGryoPitch()) + ", " + String(getGryoRoll()) + ", " + String(getGryoYaw()) + ", " + String(getPsi()) + ", " + String(getTemp());
    Serial.println(sensorCode);
    delay(50);
  }
}
