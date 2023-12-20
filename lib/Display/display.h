/**
 *  \file   display.h
 *  \author Luca Hesselbrock
 *  \date   13.12.2023
 *  \brief  Declaration of led display functionality
 *  \see    display.cpp
 */

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdint.h>
#include <page.h>

/**
 *  \class  Display
 *  \brief  The class represents the projects LCD display
 */
class Display
{
public:
    /**
     *  \brief  The constructor intializes the display instance
     */
    Display(void);

    /**
     *  \fn         show
     *  \brief      The method shows a page on the display
     *  \param[in]  page passes the page to display
     *  \see        Page
     */
    void show(const Page& page) const;

private:
    /**
     *  \fn         print
     *  \brief      The method prints a C string onto the lcd display
     *  \param[in]  str passes the characters as a pointer to a C array
     *  \note       For now, only ASCII characters will be supported!
     */
    void print(const char *str) const;

    /**
     *  \fn         send
     *  \brief      The method write the byte as two seperate nibbles
     *  \param[in]  byte passes the byte to send of type uint8_t
     *  \param[in]  mode passes the mode for sending the bytes
     */
    void send(const uint8_t &byte, const uint8_t &mode) const;

    /**
     *  \fn 	    write4Bits
     *  \brief      Writes 4 bits to the driver and toggles pulse
     *  \param[in]  byte passses the byte (nibble) to write
     */
    void Display::write4Bits(const uint8_t &byte) const;

    /**
     *  \fn         writeByte
     *  \brief      The method writes a byte to the display driver
     *  \param[in]  byte passes the byte to send of type uint8_t
     *  \note       The method should not be used for direct communication!
     *  \see        sendByteAsNibbles
     */
    void writeByte(const uint8_t &byte) const;

    /**
     *  \fn         pulseEnable
     *  \brief      The method writes the byte and toggles the third LSB
     *  \param[in]  byte passes the byte to send of type uint8_t
     */
    void pulseEnable(const uint8_t &byte) const;

    /**
     *  \fn         executeCommand
     *  \brief      The method executes a command on the display driver
     *  \param[in]  command passes the command as a byte of type uint8_t
     *  \param[in]  state passes the target state for the command
     *  \note       Members storing the command states may be changed by this method!
     *  \see
     */
    void executeCommand(const uint8_t &command, const bool &state);

    /**
     *  \enum   Command
     *  \brief  Enumeration for commands to apply on the display driver
     *  \value  Blink (0x01)
     *  \value  Cursor (0x02)
     *  \value  Display (0x04)
     *  \value  Backlight (0x08)
     *  \note   The enum value represents the bit mask for the command
     */
    enum class Command
    {
        Blink = 0x01,
        Cursor = 0x02,
        Display = 0x04,
        Backlight = 0x08
    };

    /**
     *  \var    _i2cAddress
     *  \brief  The member stores the displays I2C address
     *  \value  0x28
     */
    const uint8_t _i2cAddress = 0x28;

    /**
     *  \var    blinkEnabled
     *  \brief  The member stores wether blinking is enabled or not
     *  \value  false (default)
     */
    bool blinkEnabled = false;

    /**
     *  \var    cursorEnabled
     *  \brief  The member stores wether cursor is enabled or not
     *  \value  false (default)
     */
    bool cursorEnabled = false;

    /**
     *  \var    displayEnabled
     *  \brief  The member stores wether display is enabled or not
     *  \value  false (default)
     */
    bool displayEnabled = false;

    /**
     *  \var    backlightEnabled
     *  \brief  The member stores wether display is enabled or not
     *  \value  false (default)
     */
    bool backlightEnabled = false;
};

#endif //__DISPLAY_H__
