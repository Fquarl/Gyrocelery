/**
 *  \file   display.cpp
 *  \author Luca Hesselbrock
 *  \date   13.12.2023
 *  \brief  Implementation of led display functionality
 *  \see    display.h
 */

#include "display.h"
#include "../i2c_driver.h"

/*  Implementations  */

Display::Display(void)
{
    // Initialize the lcd display
}

void Display::print(const char *str) const
{
    // Print the string to the display
}

void Display::sendByteAsNibbles(const uint8_t &byte) const
{
    // Send the byte as two seperate nibbles (as MSB in a new byte)
    const uint8_t higherNibble = byte & 0xf0;
    const uint8_t lowerNibble = (byte << 4) & 0xf0;

    // Write the two bytes with pulse
}

void Display::writeByte(const uint8_t &byte) const
{
    // Write a byte to the display driver
    i2c_startCondition();
    i2c_sendAddressWrite(_i2cAddress);
    i2c_writeByte(byte);
    i2c_stopCondition();
}