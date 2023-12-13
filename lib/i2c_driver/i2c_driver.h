// TODO: Setupfunktion für i2c
// TODO: Fehlerstatus aus TWSR erkennen, statt nur mit while zu warten

#ifndef I2C_DRIVER_H
#define I2C_DIVER_H

#include <Arduino.h>

void i2c_init();

void i2c_startCondition();
void i2c_repeatedStartCondition();
void i2c_stopCondition();

int i2c_sendAddressWrite(const int address);
int i2c_sendAddressRead(const int address);

int i2c_sendData(int data);

void i2c_writeByte(int _byte);
int i2c_readByte(bool continueTransfer = false);

int i2c_writeWord(int address, int peripheralRegister, int data);
int i2c_readWord(int address, int peripheralRegister, char* data);

int i2c_readDWord(int address, int peripheralRegister, int* data);
int i2c_readNDwords(int address, int startRegister, int* dataArray, int len);

#endif
