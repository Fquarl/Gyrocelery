// TODO: Setupfunktion für i2c
// TODO: Fehlerstatus aus TWSR erkennen, statt nur mit while zu warten

#ifndef I2C_DRIVER_H
#define I2C_DIVER_H

#include <Arduino.h>
    /**
     *  \fn         i2c_init
     *  \brief      This method initializes the i2c bus. Not register values are calculated
     */
void i2c_init();

    /**
     *  \fn         i2c_startCondition
     *  \brief      The method sends a start condition on the bus.
     */
void i2c_startCondition();


    /**
     *  \fn         i2c_repeatedStartCondition
     *  \brief      The method sends a repeated start condition on the bus.
     */
void i2c_repeatedStartCondition();


    /**
     *  \fn         i2c_stopCondition
     *  \brief      The method sends a stop condition on the bus.
     */
void i2c_stopCondition();


    /**
     *  \fn         i2c_sendAddressWrite
     *  \brief      The method sends an adress with write postfix to the bus
     *  \param[in]  The address of the peripheral.
     */
int i2c_sendAddressWrite(const int address);


    /**
     *  \fn         i2c_sendAddressRead
     *  \brief      The method sends an adress with read postfix to the bus
     *  \param[in]  The address of the peripheral.
     */
int i2c_sendAddressRead(const int address);


    /**
     *  \fn         i2c_startCondition
     *  \brief      The method sends a start condition on the bus.
     */
int i2c_sendData(int data);


    /**
     *  \fn         i2c_writeByte
     *  \brief      The method sends databyte to the bus.
     *  \param[in]  The byte to be send.
     */
void i2c_writeByte(int _byte);


    /**
     *  \fn         i2c_readByte
     *  \brief      The method reads a byte of data from the bus. If not otherwise specified, a single byte will be read and NACK will be answered. If specified by the parameter, the transfer will be allowed to continue (ACK as answer).
     *  \param[in]  Set to true, if the bus-transfer is supposed to continue after the read byte. Default is false.
     *  \returns  The data read from the bus
     */
int i2c_readByte(bool continueTransfer = false);


    /**
     *  \fn         i2c_writeWord
     *  \brief      The method sends a byte of data to a given peripheral to a given register.
     *  \param[in]  The address of the peripheral.
     *  \param[in]  The register on the peripheral.
     *  \param[in]  The data to be send to the peripheral.
     */
int i2c_writeWord(int address, int peripheralRegister, int data);


    /**
     *  \fn         i2c_readWord
     *  \brief      The method reads a byte of data from a given peripheral from a given register.
     *  \param[in]  The address of the peripheral.
     *  \param[in]  The register on the peripheral
     *  \param[inOut]  Pointer, in wich the data will be written. 
     */
int i2c_readWord(int address, int peripheralRegister, char* data);


    /**
     *  \fn         i2c_readDWord
     *  \brief      The method reads a Dword (two bytes) of data from a given peripheral from a given register.
     *  \param[in]  The address of the peripheral.
     *  \param[in]  The register on the peripheral
     *  \param[inOut]  Pointer, in wich the data will be written. 
     */
int i2c_readDWord(int address, int peripheralRegister, int* data);


    /**
     *  \fn         i2c_readNDwords
     *  \brief      The method reads multiple Dwords (two bytes) of data from a given peripheral from a given register. The amount of Dwords read can be specified.
     *  \param[in]  The address of the peripheral.
     *  \param[in]  The register on the peripheral
     *  \param[inOut]  Pointer, in wich the data will be written. Points to an integer array of length n. The array has to be big enough for the amount of data read.
     *  \param[in]  The amount of Dwords to read.
     */
int i2c_readNDwords(int address, int startRegister, int* dataArray, int len);

#endif
