#include "i2c_driver.h"

// Nach Datenblatt ATMEGA32 S172ff 

void i2c_init() {
  // my source is that i made it up
  TWBR = 0b01001000;
}

void i2c_startCondition()
{
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT))); // warten auf senden
  while ((TWSR & 0xF8) != 0x08); // warten auf korrekten Status. Kann nur 0x08 sein
}

void i2c_repeatedStartCondition()
{
  // Repeated Start senden
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT))); // warten auf senden
  while ((TWSR & 0xF8) != 0x10); // warten auf korrektne Status. Kann nur 0x10 sein
}

void i2c_stopCondition()
{
    TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
    while((TWCR & (1<<TWSTO)));
    delay(1); 
}

int i2c_sendAddressWrite(const int address)
{
  // Adresse schreiben
  TWDR = (address << 1) | 0b0;
  
  // Daten senden
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT))); // warten auf senden
  while ((TWSR & 0xF8) != 0x18) // warten auf korrekten Status
  {
    if ((TWSR & 0xF8) == 0x20) return (TWSR & 0xF8); // SLA+W transmitted, NACK received
    if ((TWSR & 0xF8) == 0x38) return (TWSR & 0xF8); // Arbitration lost
  }
  return (TWSR & 0xF8);
}

int i2c_sendAddressRead(const int address)
{
  TWDR = (address << 1) | 0b1;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT))); // warten auf senden
  while ((TWSR & 0xF8) != 0x40) // warten auf korrekten Status
  {
    if ((TWSR & 0xF8) == 0x38) return (TWSR & 0xF8); // Arbitration lost or NACK-bit
    if ((TWSR & 0xF8) == 0x48) return (TWSR & 0xF8); // SLA+R transmitted, NACK received
  }
  return (TWSR & 0xF8);
}

int i2c_sendData(int data)
{
  // Register senden
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT))); // warten auf senden
  while ((TWSR & 0xF8) != 0x28)
  {
    if ((TWSR & 0xF8) == 0x30) return (TWSR & 0xF8); // Data transmitted, NACK received
    if ((TWSR & 0xF8) == 0x38) return (TWSR & 0xF8); // Arbitration lostt
  }
  return (TWSR & 0xF8);
}

int i2c_readByte(bool continueTransfer)
{
  TWCR = ((1 << TWINT) | (1 << TWEN) | (continueTransfer << TWEA)); // Daten in TWDR empfangen
  while ( !(TWCR & (1 << TWINT)));
  return TWDR;
}

int i2c_writeWord(int address, int peripheralRegister, int data)
{
  int lastStatus = 0;
  i2c_startCondition();
  lastStatus = i2c_sendAddressWrite(address);
  if(lastStatus == 0x20 || lastStatus == 0x38) {
    
    i2c_stopCondition();
    return lastStatus;
  }
  
  lastStatus = i2c_sendData(peripheralRegister);
  if(lastStatus == 0x30 || lastStatus == 0x38) {
    
    i2c_stopCondition();
    return lastStatus;
  }

  lastStatus = i2c_sendData(data);
  i2c_stopCondition();
  return lastStatus;  
}

int i2c_readWord(int address, int peripheralRegister, char* data)
{
  int lastStatus = 0;
  i2c_startCondition();
  lastStatus = i2c_sendAddressWrite(address);
  if(lastStatus == 0x20 || lastStatus == 0x38) {
    
    i2c_stopCondition();
    return lastStatus;
  }
  
  i2c_sendData(peripheralRegister);
  if(lastStatus == 0x30 || lastStatus == 0x38) {
    
    i2c_stopCondition();
    return lastStatus;
  }
  
  i2c_repeatedStartCondition();
  
  lastStatus = i2c_sendAddressRead(address);
  if(lastStatus == 0x38 || lastStatus == 0x48) {
    
    i2c_stopCondition();
    return lastStatus;
  }
  
  *data = i2c_readByte();
  
  i2c_stopCondition();
  return lastStatus;
}

int i2c_readDWord(int address, int peripheralRegister, int* data)
{
  
  int lastStatus = 0;
  i2c_startCondition();
  lastStatus = i2c_sendAddressWrite(address);
  if(lastStatus == 0x20 || lastStatus == 0x38) {
    i2c_stopCondition();
    return lastStatus;
  }
  
  i2c_sendData(peripheralRegister);
  if(lastStatus == 0x30 || lastStatus == 0x38) {
    i2c_stopCondition();
    return lastStatus;
  }
  
  i2c_repeatedStartCondition();
  
  lastStatus = i2c_sendAddressRead(address);
  if(lastStatus == 0x38 || lastStatus == 0x48) {
    i2c_stopCondition();
    return lastStatus;
  }

  *data = 0;
  *data |= i2c_readByte(true); // Daten speichern, ack senden, weitere Daten empfangen
  *data |= i2c_readByte(false) << 8; // Daten speichern, nack senden, Transfer beenden
  
  i2c_stopCondition();
  return lastStatus;
}

int i2c_readNDwords(int address, int startRegister, int* dataArray, int len) {
  if(len <= 0) return 0;
  
  int lastStatus = 0;
  i2c_startCondition();
  lastStatus = i2c_sendAddressWrite(address);
  if(lastStatus == 0x20 || lastStatus == 0x38) {
    i2c_stopCondition();
    return lastStatus;
  }
  
  i2c_sendData(startRegister);
  if(lastStatus == 0x30 || lastStatus == 0x38) {
    i2c_stopCondition();
    return lastStatus;
  }
  
  i2c_repeatedStartCondition();
  
  lastStatus = i2c_sendAddressRead(address);
  if(lastStatus == 0x38 || lastStatus == 0x48) {
    i2c_stopCondition();
    return lastStatus;
  }

  const int byteSum = len * 2;
  byte dataRaw[byteSum];
  for(int i = 0; i < byteSum; i++) {
    dataRaw[i] = i2c_readByte(i + 1 != byteSum);
  }

  for(int i = 0; i < len; i++) {
    dataArray[i] = (dataRaw[i * 2 + 1] << 8) | dataRaw[i * 2];
  }
  
  
  i2c_stopCondition();
  return lastStatus;
}
