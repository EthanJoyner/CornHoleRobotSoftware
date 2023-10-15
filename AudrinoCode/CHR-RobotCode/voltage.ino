#define inputVoltage A0

bool initVolts(){
  pinMode(inputVoltage, OUTPUT);
  return true;
}