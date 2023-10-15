#define valve 38
#define compressor 39


void initPnuSys() {
  pinMode(compressor, OUTPUT);
  pinMode(valve, OUTPUT);
}

int shouldFire(int a, int b) {
  if (a == 1 && b == 1) {
    digitalWrite(valve, LOW);
  } else {
    digitalWrite(valve, HIGH);
  }
}

bool adjPsi() {
  if (roboPsi < targetPSI) {
    digitalWrite(compressor, LOW);
  } else {
    digitalWrite(compressor, HIGH);
  }
}
