#define piezo 2
void setup() {
  // put your setup code here, to run once:
pinMode(piezo, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("Trigger Count 1");
  tone(piezo,10);
  delay(1000);
  noTone(piezo);
  tone(piezo,10);
  delay(1000);
  noTone(piezo);
  
  delay(5000);


}
