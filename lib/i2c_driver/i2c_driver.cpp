#include "i2c_driver.h"

void i2c_startCondition()
{
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT))); // warten auf senden
  while ((TWSR & 0xF8) != 0x08); // warten auf ack
}

void i2c_repeatedStartCondition()
{
  // Repeated Start senden
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT))); // warten auf senden
  while ((TWSR & 0xF8) != 0x10)
  {
    if ((TWSR & 0xF8) == 0x20) break; // prueft acknowledgement
    if ((TWSR & 0xF8) == 0x38) break; // prueft acknowledgement
  }
}

void i2c_sendAddressWrite(const int address)
{
// Adresse schreiben
  TWDR = (address << 1) | 0b0;
  
  // Daten senden
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT))); // warten auf senden
  while ((TWSR & 0xF8) != 0x18)
  {
    // if ((TWSR & 0xF8) == 0x20) break; // prueft acknowledgement
    // if ((TWSR & 0xF8) == 0x38) break; // prueft acknowledgement
  }
}

void i2c_sendAddressRead(const int address)
{
  TWDR = (address << 1) | 0b1;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT))); // warten auf senden
}

void i2c_stopCondition()
{
    TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);  // Setzt TWI interrupt flag zurueck, legt Stoppbedingung an SDA, Enable TWI
    while((TWCR & (1<<TWSTO))); 
}

void i2c_sendData(int data)
{
  // Register senden
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT))); // warten auf senden
  while ((TWSR & 0xF8) != 0x18)
  {
    if ((TWSR & 0xF8) == 0x20) break; // prueft acknowledgement
    if ((TWSR & 0xF8) == 0x38) break; // prueft acknowledgement
  }
}

void i2c_writeByte(int _byte)
{ 
  TWDR=_byte;           // legt Data ins Senderegister
  TWCR=(1<<TWINT)|(1<<TWEN);    // Setzt TWI interrupt flag zurueck, Enable TWI
  while (!(TWCR & (1<<TWINT))); // wartet bis TWDR uebertragen ist
  while((TWSR & 0xF8) != 0x28); // prueft acknoledgement
}

int i2c_readByte()
{
  TWCR = ((1 << TWINT) | (1 << TWEN) | (0 << TWEA));
  while ( !(TWCR & (1 << TWINT)));
  return TWDR;
}
