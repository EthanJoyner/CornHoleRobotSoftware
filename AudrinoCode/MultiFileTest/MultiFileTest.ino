void setup() {
  piezoSetup();
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0){
    int hz = Serial.readString().toInt();
    Serial.println("Boot");
    piezoBoot();
    delay(2000);
    
    Serial.println("Inspection Passed");
    piezoInspPass();
    delay(2000);

    Serial.println("Inspection Failed");
    piezoInspFail();
    delay(2000);

    Serial.println("Trigger 1");
    for (int i = 0; i<100;i++){
      piezoTrg1();
    }
    delay(2000);

    Serial.println("Trigger 2");
    for (int i = 0; i<100;i++){
      piezoTrg2();
    }
    delay(2000);

    Serial.println("Countdown");
    piezoCountDown();
    delay(2000);

    Serial.println("Fire");
    piezoFire();
    delay(2000);

    Serial.println("Cancel");
    piezoCancel(); 
  }
}
