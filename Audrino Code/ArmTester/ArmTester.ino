#define linAct 3
int armValue = 60;

void setup() {
  // put your setup code here, to run once:
  pinMode(linAct, OUTPUT);
  Serial.begin(9600); 
  Serial.setTimeout(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    int dataIn = Serial.readString().toInt();
    Serial.println(dataIn);
    switch (dataIn){
      case 1: Serial.println("Up"); break;
      case 2: Serial.println("Down"); break;
      default: Serial.println("STOP");   
    }
  }
  if (armValue < 60){
    armValue = 60;
  } else if (armValue > 150){
    armValue = 150;
  }

  analogWrite(linAct,armValue);

  }


