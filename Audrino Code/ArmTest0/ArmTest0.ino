#define la 3
void setup() {
  // put your setup code here, to run once:
  pinMode(la, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i <=51; i++){
    int output = i*5;
    analogWrite(la,i*5);
    Serial.println(output);
    delay(1000);
  }
  for(int i = 51; i >=0; i--){
    int output = i*5;
    analogWrite(la,i);
    Serial.println(output);
    delay(1000);
  }
}
