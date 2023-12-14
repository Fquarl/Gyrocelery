#ifndef LSM9DS1_H
#define LSM9DS1_H

#include <Arduino.h>
#include "LSM9DS1_Registers.h"

#define ODR_OFF 0b000
#define ODR_14  0b001
#define ODR_59  0b010
#define ODR_119 0b011
#define ODR_238 0b100
#define ODR_476 0b101
#define ODR_952 0b110

#define MaxInt 0x7FFF

class AccelPrescale {
  public:
    static const int prescale2g = 0b00;
    static const int prescale4g = 0b10;
    static const int prescale8g = 0b11;
    static const int prescale16g = 0b01;
    static const int factors[4] = {2, 16, 4, 8};
};

class GyroPrescale {
  public:
    static const int prescale245dps = 0b00;
    static const int prescale500dps = 0b01;
    static const int prescale2000dps = 0b11;
    static const int factors[4] = {245, 500, 0, 2000};
};

class accelGyroOdr {
  public:
    static const int ODROff = 0b000;
    static const int ODR14  = 0b001;
    static const int ODR59  = 0b010;
    static const int ODR119 = 0b011;
    static const int ODR238 = 0b100;
    static const int ODR476 = 0b101;
    static const int ODR952 = 0b110;
};

class LSM9DS1{
  public:
    LSM9DS1(int accelGyro = ACELGYRO_ADR, int magneto = MAGNETO_ADR);
    void softreset();   // done
    void setODR(const int ODR); // done
    void setAccelPrescale(const int scaler); // done
    void setGyroPrescale(const int scaler);  // done
    void getGyroDataRaw(int* dataArray);
    void getGyroData(double* dataArray);

  private:
    int accelGyroAddr;
    int magnetoAddr;
    int accelPrescale = 2;
    int gyroPrescale = 245;
    int currentODR; 
};




#endif
