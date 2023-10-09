#define LA 3 
void setup() {
  // put your setup code here, to run once:
  pinMode(LA, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    int target = Serial.readString().toInt();
    analogWrite(LA,target);
    delay(1000);
  }
}
