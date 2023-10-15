// Download the jarzebski MPU6050 library on github
#include <MPU6050.h>

MPU6050 mpu;
// unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch, roll, yaw = 0;

bool initGryo() {
  // Initialize MPU6050
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();
  mpu.setThreshold(3);
  return true;
}

float getGryoPitch() {
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();
  Vector norm = mpu.readNormalizeGyro();
  pitch = pitch + norm.YAxis * timeStep;
  return pitch;
}
float getGryoYaw() {
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();
  Vector norm = mpu.readNormalizeGyro();
  yaw = yaw + norm.ZAxis * timeStep;
  return yaw;
}
float getGryoRoll() {
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();
  Vector norm = mpu.readNormalizeGyro();
  roll = roll + norm.XAxis * timeStep;
  return roll;
}