// Download DallasTempature
#include <OneWire.h>
#include <DallasTemperature.h>

#define robotTemp 4

OneWire oneWire(robotTemp);
DallasTemperature sensors(&oneWire);

bool initTemp() {
  sensors.begin();
  return true;
}

float getTemp() {
  return sensors.getTempFByIndex(0);  // Use a simple function to print out the data
}
