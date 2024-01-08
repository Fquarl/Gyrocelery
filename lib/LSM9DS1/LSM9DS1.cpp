#include "LSM9DS1.h"
#include "../i2c_driver/i2c_driver.h"

const int AccelPrescale::factors[4] = {2, 16, 4, 8};
const int GyroPrescale::factors[4] = {245, 500, 0, 2000};

LSM9DS1::LSM9DS1(const int accelGyro, const int magneto):
  accelGyroAddr(accelGyro), magnetoAddr(magneto)
  {
}


void LSM9DS1::setAccelPrescale(const int scaler) {
  accelPrescale = AccelPrescale::factors[scaler];
  char currentRegister;
  int status = i2c_readWord(accelGyroAddr, CTRL_REG6_XL, &currentRegister);
  currentRegister = currentRegister & 0b11100111;
  currentRegister = currentRegister | (scaler << 3);
  i2c_writeWord(accelGyroAddr, CTRL_REG6_XL, currentRegister); 
}

void LSM9DS1::setGyroPrescale(const int scaler) {
  gyroPrescale = GyroPrescale::factors[scaler];
  char currentRegister;
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
  char lastStatus;
  int status = i2c_readWord(accelGyroAddr, CTRL_REG1_G, &lastStatus);
  
  if(status != 0x40) return;
  char newRegister = lastStatus & 0b00011111;
  newRegister = newRegister | ODR << 5;
  i2c_writeWord(accelGyroAddr, CTRL_REG1_G, newRegister);
}

void LSM9DS1::setGyroHighPassFilter(bool enable) {
  char currentSetting;
  int  status = i2c_readWord(accelGyroAddr, CTRL_REG3_G, &currentSetting);
  if(status != 0x40) return;

  unsigned char newSetting;
  unsigned char highPassEnable;
  unsigned char cutoffFrequency;
  if (true == enable) {
    cutoffFrequency = 0b00000111;
    highPassEnable = 0b01000000;
    newSetting = currentSetting | highPassEnable | cutoffFrequency ;
  }
  else {

  }
    
  i2c_writeWord(accelGyroAddr, CTRL_REG3_G, newSetting);
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
  double data[3] = {0, 0, 0};
  double* accelData = data;

  if(existingData) {
    accelData = existingData;
  } else {

    getAccelData(accelData);
  }
  
  double totalAccel = accelData[0] * accelData[0] +
                      accelData[1] * accelData[1] + 
                      accelData[2] * accelData[2];
  // totalAccel = sqrt(totalAccel);
  return totalAccel; 
}

/*
void LSM9DS1::getSphericAccel(double* coords) {
  double* accelData;
  getAccelData(accelData);
  coords[0] = getTotalAccel(accelData);
  coords[1] = acos(accelData[2] / coords[0]);
  coords[2] = atan2(accelData[1], accelData[0]);
}
*/

void LSM9DS1::setFifo(bool enable) {
  char currentSetting;
  int status = i2c_readWord(accelGyroAddr, CTRL_REG9, &currentSetting); // Muss der Rückgabewert der funktion gelesen werden?
  unsigned char FIFO_EN;
  unsigned char fMode;
  if(enable == true) {
    FIFO_EN = 0b11111111;
    fMode = fifoMode;
  }
  else {
    FIFO_EN = 0b11111101;
    fMode = 0;
  }
  int ctrlRegSetting = (currentSetting & FIFO_EN);                   // Enable FIFO in CTRL Register
  i2c_writeWord(accelGyroAddr, CTRL_REG9, ctrlRegSetting);

  int fifoCtrlRegSetting = ((fMode << 5) |  fifoThreshholdSize);
  i2c_writeWord(accelGyroAddr, FIFO_CTRL, fifoCtrlRegSetting);
}

void LSM9DS1::setFifoInterrupt(void) {
  char currentSetting;
  int status = i2c_readWord(accelGyroAddr, INT1_CTRL, &currentSetting); // Muss der Rückgabewert der funktion gelesen werden?
  int interruptRegSetting = (currentSetting | 0b00001000);              //FIFO threshold interrupt on INT 1_A/G pin. Default value: 0
  i2c_writeWord(accelGyroAddr, INT1_CTRL, interruptRegSetting);
}

void LSM9DS1::readFifo(void) {
  char numberOfSamples;
  i2c_readWord(accelGyroAddr, FIFO_SRC, &numberOfSamples);
  numberOfSamples = (numberOfSamples & 0x3F);
  for (int i = 0; i < numberOfSamples; i++)                             // Read the gyro data stored in the FIFO
  { 
    double accelDataArray[3];
    getAccelData(accelDataArray);
    storedFifoData->xAccel[i] = accelDataArray[0];
    storedFifoData->yAccel[i] = accelDataArray[1];
    storedFifoData->zAccel[i] = accelDataArray[2];
    double gyroDataArray[3];
    getGyroData(gyroDataArray);
    storedFifoData->roll[i] = gyroDataArray[0];
    storedFifoData->pitch[i] = gyroDataArray[1];
    storedFifoData->yaw[i] = gyroDataArray[2];
  }
}

inertialModuleData* LSM9DS1::getStoredData(void) {
return storedFifoData;
}
