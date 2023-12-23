#define piezo 2
#define T1 1500
#define T2 2000
#define T3 3000
#define T4 4000
#define T5 4500
#define stopDelay 100
void initPiezo() {
  // put your setup code here, to run once:
  pinMode(piezo, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(50);
}

void piezoBoot() {
  tone(piezo, T1);
  delay(500);
  noTone(piezo);
  delay(stopDelay);

  tone(piezo, T3);
  delay(500);
  noTone(piezo);
  delay(stopDelay);

  tone(piezo, T5);
  delay(500);
  noTone(piezo);
}

void piezoInspPass() {
  tone(piezo, T4);
  delay(500);
  noTone(piezo);
  delay(stopDelay);

  tone(piezo, T5);
  delay(500);
  noTone(piezo);
  delay(stopDelay);
}

void piezoInspFail() {
  for (int i = 0; i < 3; i++)
  {
    tone(piezo, T1);
    delay(500);
    noTone(piezo);
    delay(stopDelay);
  }
}

void piezoTrg1() {
  tone(piezo, T1);
  delay(10);
  noTone(piezo);
  delay(stopDelay);
}

void piezoTrg2() {
  tone(piezo, T5);
  delay(10);
  noTone(piezo);
  delay(stopDelay);
}

void piezoCountDown() {
  tone(piezo, T5);
  delay(1000);
  noTone(piezo);
  delay(stopDelay);

  tone(piezo, T3);
  delay(1000);
  noTone(piezo);
  delay(stopDelay);

  tone(piezo, T1);
  delay(1000);
  noTone(piezo);
  delay(stopDelay);
}

void piezoFire() {
  tone(piezo, T5);
  delay(100);
  noTone(piezo);
  delay(stopDelay);
  tone(piezo, T4);
  delay(100);
  noTone(piezo);
  delay(stopDelay);
}

void piezoCancel() {
  for (int i = 0; i < 5; i++) {
    tone(piezo, T1);
    delay(100);
    noTone(piezo);
    delay(stopDelay);
  }
}
