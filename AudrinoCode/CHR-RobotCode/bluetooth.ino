bool initBluetooth() {
  // Set up Serial Channels
  Serial.begin(9600);
  Serial1.begin(9600);
  // Set Respnse time to 50ms
  Serial.setTimeout(50);
  Serial1.setTimeout(50);
  return true;
}

void readBluetooth(){
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
}