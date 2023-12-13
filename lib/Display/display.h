/**
 *  \file   display.h
 *  \author Luca Hesselbrock
 *  \date   13.12.2023
 *  \brief  Declaration of led display functionality
 *  \see    display.cpp
 */

#include <stdint.h>

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
     *  \fn         print
     *  \brief      The method prints a C string onto the lcd display
     *  \param[in]  str passes the characters as a pointer to a C array
     *  \note       For now, only ASCII characters will be supported!
     */
    void print(const char *str) const;

private:
    /**
     *  \fn         sendBytesAsNibbles
     *  \brief      The method write the byte as two seperate nibbles
     *  \param[in]  byte passes the byte to send of type uint8_t
     */
    void sendByteAsNibbles(const uint8_t &byte) const;

    /**
     *  \fn         writeByte
     *  \brief      The method writes a byte to the display driver
     *  \param[in]  byte passes the byte to send of type uint8_t
     *  \note       The method should not be used for direct communication!
     *  \see        sendByteAsNibbles
     */
    void writeByte(const uint8_t &byte) const;

    /**
     *  \var    _i2cAddress
     *  \brief  The member stores the displays I2C address
     *  \value  0x28
     */
    const uint8_t _i2cAddress = 0x28;
};