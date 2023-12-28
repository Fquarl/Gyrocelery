#ifndef LSM9DS1_H
#define LSM9DS1_H

#include <Arduino.h>
#include "LSM9DS1_Registers.h"

#define MaxInt 0x7FFF

/**
 *  \class  AccelPrescale
 *  \brief  The class defines all possible accelerometer prescaler of the LSM9DS1 and their bit-representation on the device.
 */
class AccelPrescale {
  public:
    static const int prescale2g = 0b00;
    static const int prescale4g = 0b10;
    static const int prescale8g = 0b11;
    static const int prescale16g = 0b01;
    static const int factors[4] = {2, 16, 4, 8};
};

/**
 *  \class  GyroPrecale
 *  \brief  The class defines all possible gyro prescaler of the LSM9DS1 and their bit-representation on the device.
 */
class GyroPrescale {
  public:
    static const int prescale245dps = 0b00;
    static const int prescale500dps = 0b01;
    static const int prescale2000dps = 0b11;
    static const int factors[4] = {245, 500, 0, 2000};
};

/**
 *  \class  Display
 *  \brief  The class defines all possible output data rates of the LSM9DS1.
 */
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

/**
 *  \class  LSM9DS1
 *  \brief  The class represents the LSM9DS1
 */
class LSM9DS1{
  public:
    LSM9DS1(int accelGyro = ACELGYRO_ADR, int magneto = MAGNETO_ADR);
    /**
     *  \fn         softreset
     *  \brief      The method shows performs a softreset of the device
    */

    void softreset();   // done
     /**
     *  \fn         setODR
     *  \brief      The method sets the output data rate of both the accelerometer and gyroscope.
     *  \param[in]  The desired ODR
     *  \see        accelGyroOdr
     */
    void setODR(const int ODR); // done

     /**
     *  \fn         setAccelPrescale
     *  \brief      The method sets the prescaler/fullscale range of the accelerometer
     *  \param[in]  The desired prescaler/fullscale range
     *  \see        AccelPrescale
     */
    void setAccelPrescale(const int scaler); // done
     /**
     *  \fn         setGyroPrescale
     *  \brief      The method sets the prescaler/fullscale range of the gyroscope
     *  \param[in]  The desired prescaler/fullscale range
     *  \see        GyroPrescale
     */
    void setGyroPrescale(const int scaler);  // done
     /**
     *  \fn         getGyroDataRaw
     *  \brief      The method reads all gyro axis as raw values
     *  \param[inOut]  An pointer to an integer array of size 3 containing the data. X-axis, Y-axis and Z-axis.
     */
    void getGyroDataRaw(int* dataArray);
     /**
     *  \fn         getGyroData
     *  \brief      The method reads all gyro axis as dps-value.
     *  \param[inOut]  An pointer to an double array of size 3 containing the data. X-axis, Y-axis and Z-axis.
     */
    void getGyroData(double* dataArray);
     /**
     *  \fn         getAccelDataRaw
     *  \brief      The method reads all accelerometer axis as raw values
     *  \param[inOut]  An pointer to an integer array of size 3 containing the data. X-axis, Y-axis and Z-axis.
     */
    void getAccelDataRaw(int* dataArray);
     /**
     *  \fn         getAccekData
     *  \brief      The method reads all accelerometer axis as g-values
     *  \param[inOut]  An pointer to an integer array of size 3 containing the data. X-axis, Y-axis and Z-axis.
     */
    void getAccelData(double* dataArray);
     /**
     *  \fn         getTotalAccel
     *  \brief      The method calculates the total acceleration meassured as g-value.
     *  \param[in]  An optional double-Array containing the acceleration data. If no data is provided, current data will be read from the device.
     *  \returns    The total acceleration  as g-value.
     */
    double getTotalAccel(double* existingData = nullptr);
    void getSphericAccel(double* coords);
    /**
     *  \fn         setFifoInterrupt
     *  \brief      This method enables the "FIFO threshhold reached" interrupt
     */
    void setFifoInterrupt(void);
        /**
     *  \fn         enableFIFO
     *  \brief      This method sets the FIFO mode to the "continous mode", as new data arrives the older is discarded.
     */
    void enableFIFO(void);
    void readFifo(double* gyroData, int* accelData);

  private:
    typedef struct storedGyroData; 
    int accelGyroAddr;
    int magnetoAddr;
    int accelPrescale = 2;
    int gyroPrescale = 245;
    int currentODR;
    int fifoMode = 0b110; // 0b110 Continous Mode 0b001 FIFO mode
    int fifoThreshholdSize = 0b11111; // 32 samples werden pro Achse gespeichert
};




#endif
