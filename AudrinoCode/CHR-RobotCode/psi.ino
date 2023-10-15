#include <Wire.h>

#define robotPSI 52

const int pressureInput = A0;              //select the analog input pin for the pressure transducer
const int pressureZero = 102.4;            //analog reading of pressure transducer at 0psi
const int pressureMax = 921.6;             //analog reading of pressure transducer at 100psi
const int pressuretransducermaxPSI = 100;  //psi value of transducer being used
const int sensorreadDelay = 250;           //constant integer to set the sensor read delay in milliseconds

bool initPsi() {
  pinMode(robotPSI, INPUT);
  // Check PSI Sensor
  float roboPsi = analogRead(robotPSI);                                                            //reads value from input pin and assigns to variable
  roboPsi = ((roboPsi - pressureZero) * pressuretransducermaxPSI) / (pressureMax - pressureZero);  //conversion equation to convert analog reading to psi
  return true;
}

float getPsi() {
  float roboPsi = analogRead(robotPSI);                                                            //reads value from input pin and assigns to variable
  roboPsi = ((roboPsi - pressureZero) * pressuretransducermaxPSI) / (pressureMax - pressureZero);  //conversion equation to convert analog reading to psi
  return roboPsi;
}