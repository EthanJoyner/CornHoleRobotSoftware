void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0)
{
  int dataIn = Serial.parseInt();

  //Do something with the data - like print it
  Serial.print(dataIn);
}
