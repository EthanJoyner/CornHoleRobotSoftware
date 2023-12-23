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
    readBluetooth();
    String dataIn = Serial.readString();
    if (dataIn.substring(0, 1).toInt() == 1) {
      doTeleop(dataIn);
      motorFunction(analogLeft, analogRight);
      shouldFire(playerFireReady, adminFireReady);
    } else if (dataIn.substring(0, 1).toInt() == 2) {  // If a type 2 command (sequence Command)
      doSeq(dataIn);
    } else {
      // Serial.println("No Signal...");
      // Do somethinzg with the data - like print it
      // Serial.print("Code: ");
      // Serial.println(dataIn);
    }

    // Start data Send out
    String sensorCode = String(getVolts()) + ", " + String(getGryoPitch()) + ", " + String(getGryoRoll()) + ", " + String(getGryoYaw()) + ", " + String(getPsi()) + ", " + String(getTemp());
    Serial.println(sensorCode);
    delay(50);
  }
}
