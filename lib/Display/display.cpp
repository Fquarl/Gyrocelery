/**
 *  \file   display.cpp
 *  \author Luca Hesselbrock
 *  \date   13.12.2023
 *  \brief  Implementation of led display functionality
 *  \see    display.h
 */

#include "display.h"

#include <util/delay.h>
#include "../i2c_driver.h"

/*  Implementations  */

Display::Display(void)
{
}

void Display::print(const char *str) const
{
    // Print a c string of undefined length
    const uint8_t arrayLength = sizeof(str) / sizeof(uint8_t);
    for (uint8_t i = 0; i < arrayLength; i++)
    {
        constexpr uint8_t writeModeFlag = 0x01;
        send(str[i], writeModeFlag);
    }
}

void Display::send(const uint8_t &byte, const uint8_t &mode) const
{
    // Send the byte as two seperate nibbles (as MSB in a new byte)
    const uint8_t higherNibble = byte & 0xf0;
    const uint8_t lowerNibble = (byte << 4) & 0xf0;
    write4Bits(higherNibble | mode);
    write4Bits(lowerNibble | mode);
}

void Display::write4Bits(const uint8_t &byte) const
{
    // Write the byte and toggle pulse
    writeByte(byte);
    pulseEnable(byte);
}

void Display::writeByte(const uint8_t &byte) const
{
    // Write a byte to the display driver
    i2c_startCondition();
    i2c_sendAddressWrite(_i2cAddress);
    i2c_writeByte(byte);
    i2c_stopCondition();
}

void Display::pulseEnable(const uint8_t &byte) const
{
    // Write the data twice with toggled pulse enable
    constexpr uint8_t pulseEnableMask = 0x40;
    writeByte(byte | pulseEnableMask);
    _delay_us(1);
    writeByte(byte & ~pulseEnableMask);
    _delay_us(50);
}

void Display::executeCommand(const Display::Command &command, const bool &state)
{
    // Write a command to the display driver
    switch (command)
    {
    case Command::Blink:
        blinkEnabled = state;
        break;
    case Command::Cursor:
        cursorEnabled = state;
        break;
    case Command::Display:
        displayEnabled = state;
        break;
    case Command::Backlight:
        backlightEnabled = state;
        break;
    }
    const uint8_t controlByte = (blinkEnabled ? Command::Blink : 0x00) |
                                (cursorEnabled ? Command::Cursor : 0x00) |
                                (displayEnabled ? Command::Display : 0x00) |
                                (backlightEnabled ? Command::Backlight : 0x00);
    send(controlByte, 0x00);
}
