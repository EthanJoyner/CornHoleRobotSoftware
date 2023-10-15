bool initBluetooth() {
  // Set up Serial Channels
  Serial.begin(9600);
  Serial1.begin(9600);
  // Set Respnse time to 50ms
  Serial.setTimeout(50);
  Serial1.setTimeout(50);
  return true;
}