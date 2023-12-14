#include "LSM9DS1.h"
#include <i2c_driver.h>

LSM9DS1::LSM9DS1(const int accelGyro, const int magneto):
  accelGyroAddr(accelGyro), magnetoAddr(magneto)
  {
}

void LSM9DS1::setAccelPrescale(const int scaler) {
  accelPrescale = AccelPrescale::factors[scaler];
  byte currentRegister;
  int status = i2c_readWord(accelGyroAddr, CTRL_REG6_XL, &currentRegister);
  currentRegister = currentRegister & 0b11100111;
  currentRegister = currentRegister | (scaler << 3);
  i2c_writeWord(accelGyroAddr, CTRL_REG6_XL, currentRegister); 
}

void LSM9DS1::setGyroPrescale(const int scaler) {
  gyroPrescale = GyroPrescale::factors[scaler];
  byte currentRegister;
  int status = i2c_readWord(accelGyroAddr, CTRL_REG1_G, &currentRegister);
  
  currentRegister = currentRegister & 0b11100111;
  currentRegister = currentRegister | (scaler << 3);
  i2c_writeWord(accelGyroAddr, CTRL_REG1_G, currentRegister);
  
}

void LSM9DS1::softreset() {
  i2c_writeWord(accelGyroAddr, CTRL_REG8, 0b00000001); // Software reset
  
}

void LSM9DS1::setODR(const int ODR) {
  currentODR = ODR;
  byte lastStatus;
  int status = i2c_readWord(accelGyroAddr, CTRL_REG1_G, &lastStatus);
  
  
  if(status != 0x40) return;
  byte newRegister = lastStatus & 0b00011111;
  newRegister = newRegister | ODR << 5;
  
  
}

void LSM9DS1::getGyroDataRaw(int* dataArray) {
  i2c_readNDwords(accelGyroAddr, OUT_X_L_G, dataArray, 3);
}

void LSM9DS1::getGyroData(double* dataArray) {
  int rawDataArray[3] = {0, 0, 0};
  getGyroDataRaw(rawDataArray);
  
  for(int i = 0; i < 3; i++) {
    double percent = (double)rawDataArray[i] / 0x7FFF;
    dataArray[i] = percent * gyroPrescale;
  }
}


void LSM9DS1::getAccelDataRaw(int* dataArray) {
  i2c_readNDwords(accelGyroAddr, OUT_X_L_XL, dataArray, 3);
}

void LSM9DS1::getAccelData(double* dataArray) {
  int rawDataArray[3] = {0, 0, 0};
  getAccelDataRaw(rawDataArray);
  
  for(int i = 0; i < 3; i++) {
    double percent = (double)rawDataArray[i] / 0x7FFF;
    dataArray[i] = percent * accelPrescale;
  }
}

double LSM9DS1::getTotalAccel(double* existingData) {
  double* accelData;
  if(existingData) {
    accelData = existingData;
  } else {
    getAccelData(accelData);
  }
  
  double totalAccel = accelData[0] * accelData[0] +
                      accelData[1] * accelData[1] + 
                      accelData[2] * accelData[2];
  totalAccel = sqrt(totalAccel);
  return totalAccel; 
}

void LSM9DS1::getSphericAccel(double* coords) {
  double* accelData;
  getAccelData(accelData);
  coords[0] = getTotalAccel(accelData);
  coords[1] = acos(accelData[2] / coords[0]);
  coords[2] = atan2(accelData[1], accelData[0]);
}