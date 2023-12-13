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
     *  \fn         writeByte
     *  \brief      The method writes a byte to the display driver
     *  \param[in]  byte passes the byte to send of type char
     */
    void writeByte(const uint8_t &str) const;
};