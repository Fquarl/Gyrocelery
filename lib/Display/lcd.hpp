/**
 *  \file vector.hpp
 */

#ifndef __LCD_HPP__
#define __LCD_HPP__

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

#include "../i2c_driver/i2c_driver.h"
#include "../Vector_header_only/vector.hpp"

class LCD
{
public:

    LCD(void)
    {
		init();
    }

	void printFormatted(const Vector<char>& text)
	{
		for (uint8_t n = 0; n < _rowCount; n++)
		{
			for (uint8_t i = 0; i < _columnCount; i++)
			{
				const uint8_t nextIndex = i + n * _columnCount;
				
				if (nextIndex >= _rowCount * _columnCount)
				{
					break;
				}

				setCursor(i, n);
				print(&text.at(nextIndex));
			}
		}
	}

    void print(char text[32])
    {
    	char c[32] = {};

    	strcpy(c, text);

    	uint8_t index = 0;
    	while (index < 32)
    	{
    		if (0x00 == c[index])
    		{
    			break;
    		}
    		send(c[index], RS);
    		index++;
    	}
    }

    void home(void)
    {
    	command(RETURNHOME);
    	_delay_us(2000);
    }

    void clear(void)
    {
    	command(CLEARDISPLAY);
    	_delay_us(2000);
    }

    void setCursor(const uint8_t& columnIndex, const uint8_t& rowIndex)
    {
    	const uint8_t rowOffsets[] = {0x00, 0x40, 0x14, 0x54};
		uint8_t rowIndexVolatile = rowIndex;

    	if (rowIndexVolatile > _rowCount)
    	{
    		rowIndexVolatile = _rowCount - 1;
    	}
    	command(SETDDRAMADDR | (columnIndex + rowOffsets[rowIndexVolatile]));
    }

    void backlightOnOff(const bool& state)
    {
    	if (state)
    	{
    		_backlightValue = BACKLIGHT;
    	}
    	else
    	{
    		_backlightValue = NOBACKLIGHT;
    	}
    	command(0);
    }

    void blinkOnOff(const bool& state)
    {
        if (state)
	    {
	    	_displayControl |= BLINKON;
	    }
	    else
	    {
	    	_displayControl &= ~BLINKON;
	    }
	    command(DISPLAYCONTROL | _displayControl);
    }

    void cursorOnOff(const bool& state)
    {
        if (state)
	    {
	    	_displayControl |= CURSORON;
	    }
	    else
	    {
	    	_displayControl &= ~CURSORON;
	    }
	    command(DISPLAYCONTROL | _displayControl);
    }

    void displayOnOff(const bool& state)
    {
    	if (state)
    	{
    		_displayControl |= DISPLAYON;
    	}
    	else
    	{
    		_displayControl &= ~DISPLAYON;
    	}
    	command(DISPLAYCONTROL | _displayControl);
    }

private:

    void init(void)
    {
    	_displayFunction = MODE4BIT | MODE2LINE | MODE5x8DOTS;
    
    	expanderWrite(_backlightValue);

    	enter4bitMode(); 

    	command(FUNCTIONSET | _displayFunction);
    	_displayControl = DISPLAYON | CURSOROFF | BLINKOFF;

    	displayOnOff(1);
    	clear();
    	_displayMode = ENTRYLEFT | ENTRYSHIFTDECREMENT;
    	command(ENTRYMODESET | _displayMode);
    	home();
    	backlightOnOff(1);
    }

    void sendAddress(void)
    {
	    TWDR = _lcdAddress;
	    TWCR = (1 << TWINT) | (1 << TWEN);
	    while (!(TWCR & (1 << TWINT)));
	    while ((TWSR & 0xF8) != 0x18);
    }

    void expanderWrite(const uint8_t& value)
    {
        i2c_startCondition();
	    sendAddress();
	    i2c_sendData(value | _backlightValue);
	    i2c_stopCondition();
    }

    void pulseEnable(const uint8_t& _data)
    {
	    expanderWrite(_data | EN);
	    _delay_us(1);
	    expanderWrite(_data & ~EN);
	    _delay_us(50);
    }

    void write4bits(const uint8_t& value)
    {
	    expanderWrite(value);
	    pulseEnable(value);
    }

    void send(const uint8_t& value, const uint8_t& mode)
    {
	    uint8_t highnib = value & 0xf0;
	    uint8_t lownib = (value << 4) & 0xF0;
	    write4bits((highnib) | mode);
	    write4bits((lownib) | mode);
    }

    void command(const uint8_t& value)
    {
        send(value, 0);
    }

    void leftToRight(void)
    {
    	_displayMode |= ENTRYLEFT;
    	command(ENTRYMODESET | _displayMode);
    }

    void rightToLeft(void)
    {
    	_displayMode &= ~ENTRYLEFT;
    	command(ENTRYMODESET | _displayMode);
    }

    void scrollDisplayLeft(void)
    {
    	command(CURSORSHIFT | DISPLAYMOVE | MOVELEFT);
    }

    void scrollDisplayRight(void)
    {
    	command(CURSORSHIFT | DISPLAYMOVE | MOVERIGHT);
    }

    void leftJustify(void)
    {
    	_displayMode &= ~ENTRYSHIFTINCREMENT;
    	command(ENTRYMODESET | _displayMode);
    }

    void rightJustify(void)
    {
    	_displayMode |= ENTRYSHIFTINCREMENT;
    	command(ENTRYMODESET | _displayMode);
    }

    void enter4bitMode(void)
    {
    	write4bits(0x03 << 4);
    	_delay_us(4500);
    	write4bits(0x03 << 4);
    	_delay_us(4500);
    	write4bits(0x03 << 4);
    	_delay_us(150);
    	write4bits(0x02 << 4);
    }

private:

	const uint8_t _lcdAddress = (0x27 << 1) & 0xfe;
	const uint8_t _rowCount = 2;
	const uint8_t _columnCount = 16;

	uint8_t _backlightValue = BACKLIGHT;								
	uint8_t _displayControl = DISPLAYON | CURSOROFF | BLINKOFF; 
	uint8_t _displayMode 	= ENTRYLEFT | ENTRYSHIFTDECREMENT;			
	uint8_t _displayFunction;

	const static inline uint8_t CLEARDISPLAY	 	  = 0x01;
	const static inline uint8_t RETURNHOME	 	  	  = 0x02;
	const static inline uint8_t ENTRYMODESET	 	  = 0x04;
	const static inline uint8_t DISPLAYCONTROL 	  	  = 0x08;
	const static inline uint8_t CURSORSHIFT	 	  	  = 0x10;
	const static inline uint8_t FUNCTIONSET	 	  	  = 0x20;
	const static inline uint8_t SETCGRAMADDR	 	  = 0x40;
	const static inline uint8_t SETDDRAMADDR	 	  = 0x80;
	const static inline uint8_t ENTRYRIGHT	 	  	  = 0x00;
	const static inline uint8_t ENTRYLEFT		 	  = 0x02;
	const static inline uint8_t ENTRYSHIFTINCREMENT   = 0x01;
	const static inline uint8_t ENTRYSHIFTDECREMENT   = 0x00;
	const static inline uint8_t DISPLAYON	 		  = 0x04;
	const static inline uint8_t DISPLAYOFF 		   	  = 0x00;
	const static inline uint8_t CURSORON	 		  = 0x02;
	const static inline uint8_t CURSOROFF	 		  = 0x00;
	const static inline uint8_t BLINKON	 		  	  = 0x01;
	const static inline uint8_t BLINKOFF	 		  = 0x00;
	const static inline uint8_t DISPLAYMOVE 		  = 0x08;
	const static inline uint8_t CURSORMOVE  		  = 0x00;
	const static inline uint8_t MOVERIGHT	  		  = 0x04;
	const static inline uint8_t MOVELEFT	  		  = 0x00;
	const static inline uint8_t MODE8BIT 			  = 0x10;
	const static inline uint8_t MODE4BIT 			  = 0x00;
	const static inline uint8_t MODE2LINE	   		  = 0x08;
	const static inline uint8_t MODE1LINE	   		  = 0x00;
	const static inline uint8_t MODE5x10DOTS 		  = 0x04;
	const static inline uint8_t MODE5x8DOTS  		  = 0x00;
	const static inline uint8_t BACKLIGHT	  		  = 0x08;
	const static inline uint8_t NOBACKLIGHT 		  = 0x00;
	
	const static inline uint8_t EN = 0b00000100;
	const static inline uint8_t RW = 0b00000010;
	const static inline uint8_t RS = 0b00000001;
};

#endif //__LCD_HPP__