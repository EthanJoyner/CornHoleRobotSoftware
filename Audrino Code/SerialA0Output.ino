void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
    // If there is incoming data
  if (Serial.available() > 0) {

    // Write the data to the serial port
    Serial.println("I received: " + Serial.readString());
  }

  // put your main code here, to run repeatedly:
  int value = analogRead(A0);
  float voltage = value * (5.0/1024.0);
  Serial.println(voltage);
  
}
