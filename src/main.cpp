/**
 *  \file main.cpp
 *  
 *  This file contains the main execution cycle.
 *  For now it contians the control for the display.
 */

#include "../lib/lcd.hpp"

int main(void)
{
    LCD display;
    Vector<char> text;
    text << "Guten Abend, mein Name ist Luca!";

    while (true)
    {
        display.printFormatted(text);
        _delay_ms(1000);
    }

    return 0;
}