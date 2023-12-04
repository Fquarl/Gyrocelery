// TODO: Setupfunktion für i2c
// TODO: Fehlerstatus aus TWSR erkennen, statt nur mit while zu warten

#ifndef I2C_DRIVER_H
#define I2C_DIVER_H

#include <Arduino.h>

void i2c_startCondition();
void i2c_repeatedStartCondition();
void i2c_sendAddressWrite(const int address);
void i2c_sendAddressRead(const int address);
void i2c_stopCondition();
void i2c_sendData(int data);
void i2c_writeByte(int _byte);
int i2c_readByte();

#endif
