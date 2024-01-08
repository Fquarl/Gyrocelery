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

	/**
	 *	\fn 	LCD
	 * 	\brief	The constructor initializes the instance of type 'LCD'
	 */
    LCD(void);

	/**
	 *	\fn 		printFormatted
	 * 	\brief		The method prints a formatted string vector on the display
	 * 	\param[in]	text passes the ccharacters in a custom vector
	 */
	void printFormatted(const Vector<char>& text);

	/**
	 *	\fn 		print
	 * 	\brief		The method prints a C string on the display
	 * 	\param[in]	text passes the characters as a C string
	 */
    void print(char text[32]);

	/**
	 *	\fn 	home
	 * 	\brief	The method makes the display return home position
	 */
    void home(void);

	/**
	 *	\fn 	clear
	 * 	\brief	The method clears the display
	 */
    void clear(void);

	/**	
	 * 	\fn			setCursor
	 * 	\brief		The method sets the cursor where the next char gets printed
	 * 	\param[in]	columnIndex passes the x position to set the cursor to 
	 * 	\param[in]	rowIndex passes the y position to set the cursor to
	 */
    void setCursor(const uint8_t& columnIndex, const uint8_t& rowIndex);

	/**
	 *	\fn 		backlightOnOff
	 * 	\brief		The method enables/disables the backlight of the display
	 * 	\param[in]	state passes the state to set the backlighting to
	 */
    void backlightOnOff(const bool& state);

	/**
	 *	\fn 		blinkOnOff
	 * 	\brief		The method enables/disables the blink of the display
	 * 	\param[in]	state passes the state to set the blink to
	 */
    void blinkOnOff(const bool& state);

	/**
	 *	\fn 		cursorOnOff
	 * 	\brief		The method enables/disbales the cursor of the display
	 * 	\param[in]	state passes the state to set the cursor visibility to
	 */
    void cursorOnOff(const bool& state);

	/**
	 *	\fn 		displayOnOff
	 * 	\brief		The method enables/disables the display 
	 * 	\param[in]	satte passe the state to set the display to
	 */
    void displayOnOff(const bool& state);

private:

	/**
	 *	\fn 	init
	 * 	\brief	The method initializes the communication to the display 
	 */
    void init(void);


	/**
	 *	\fn 		sendAddress
	 * 	\brief		The method sends the displays address to the I2C bus 
	 * 	\todo		Fix the I2C library! 
	 * 	\deprecated	
	 */
    void sendAddress(void);

	/**
	 *	\fn 		expanderWrite
	 * 	\brief		Basic communication method to address the display
	 * 	\param[in]	value passes the byte to write
	 */
    void expanderWrite(const uint8_t& value);

	/**
	 *	\fn 		pulseEnable
	 * 	\brief		The method toggles byte at index 2 while writing 
	 * 	\param[in]	value passes the byte to write
	 */
    void pulseEnable(const uint8_t& value);

	/**
	 *	\fn 		write4Bits
	 * 	\brief		The method sends a nibble to the display
	 * 	\param[in]	value passes the nibble to send in byte
	 */
    void write4bits(const uint8_t& value);

	/**	
	 * 	\fn			send
	 * 	\brief		The method sends a byte in a specific mode to the display
	 * 	\param[in]	value passes the byte to send to the display
	 * 	\param[in]	mode passes the operation mode to use
	 */
    void send(const uint8_t& value, const uint8_t& mode);

	/**
	 *	\fn 		command
	 * 	\brief		The method executes a command on the display driver	
	 * 	\param[in]	value passes the commands value to send
	 */
    void command(const uint8_t& value);

	/**
	 *	\fn 	leftToRight
	 * 	\brief	The method specifies the writing direction (left to right)
	 */
    void leftToRight(void);

	/**
	 *	\fn 	rightToLeft
	 * 	\brief	The method specifies the writing direction (right to left)
	 */	
    void rightToLeft(void);

	/**
	 *	\fn 	scrollDisplayLeft
	 * 	\brief	The method scrolls the display to the left side
	 */
    void scrollDisplayLeft(void);

	/**			
	 *	\fn 	scrollDisplayRight
	 * 	\brief	The method scrolls the display to the right side
	 */
    void scrollDisplayRight(void);

	/**
	 *	\fn 	leftJusitfy
	 * 	\brief	The method justifies the text to the left side
	 */
    void leftJustify(void);

	/**
	 *	\fn 	rightJusitify
	 * 	\brief	The method justifies the text to the right side
	 */
    void rightJustify(void);

	/**
	 *	\fn 	enter4bitMode
	 * 	\brief	The method specifies the 4 bit communication to the display driver
	 */
    void enter4bitMode(void);

private:

	/**
	 *	\var 	_lcdAddress
	 * 	\brief	The displays I2C address
	 * 	\value	0x4e
	 */
	const uint8_t _lcdAddress = (0x27 << 1) & 0xfe;
	
	/**
	 *	\var	_rowCount 
	 * 	\brief	The displays count of rows
	 * 	\value	2
	 */
	const uint8_t _rowCount = 2;
	
	/**
	 *	\var 	_columnCount
	 * 	\brief	The displays count of columns
	 * 	\value	16
	 */
	const uint8_t _columnCount = 16;

	/**
	 *	\var 	_backlightValue	
	 * 	\brief	The stored backlighting setting
	 * 	\value	Default: 0x08 (BACKLIGHT)
	 */
	uint8_t _backlightValue = BACKLIGHT;
	
	/**
	 *	\var 	_displayControl
	 * 	\brief	The stored display control settings
	 * 	\value	Default: 0x04 (DISPLAYON)
	 */								
	uint8_t _displayControl = DISPLAYON | CURSOROFF | BLINKOFF; 
	
	/**
	 *	\var 	_displayMode
	 * 	\brief	The stored display mode settings
	 * 	\value	Default: 0x02 (ENTRYLEFT)
	 */
	uint8_t _displayMode = ENTRYLEFT | ENTRYSHIFTDECREMENT;		
	
	/**
	 *	\var 	_displayFunction
	 * 	\brief	The stored display function settings
	 * 	\value	Default: 0x00
	 */	
	uint8_t _displayFunction = 0x00;

	/**
	 *	\var 	CLEARDISPLAY
	 * 	\brief	The command to clear the display
	 * 	\value	0x01
	 */
	const static inline uint8_t CLEARDISPLAY = 0x01;
	
	/**
	 *	\var 	RETURNHOME
	 * 	\brief	The command to return the display to home 
	 * 	\value	0x02
	 */
	const static inline uint8_t RETURNHOME = 0x02;
	
	/**
	 *	\var 	ENTRYMODESET
	 * 	\brief	The command to set the entry mode
	 * 	\value	0x04
	 */
	const static inline uint8_t ENTRYMODESET = 0x04;
	
	/**
	 *	\var 	DISPLAYCONTROL
	 * 	\brief	The display control addressing command
	 * 	\value	0x08
	 */
	const static inline uint8_t DISPLAYCONTROL = 0x08;
	
	/**
	 *	\var 	CURSORSHIFT
	 * 	\brief	The cursor shift addressing command
	 * 	\value	0x10
	 */
	const static inline uint8_t CURSORSHIFT = 0x10;
	
	/**
	 *	\var 	FUNCTIONSET
	 * 	\brief	The functionset addressing command
	 * 	\value
	 */
	const static inline uint8_t FUNCTIONSET	= 0x20;
	
	/**
	 *	\var 	SETCGRAMADDR
	 * 	\brief	The CGRAM addressing selector command
	 * 	\value	0x40
	 */
	const static inline uint8_t SETCGRAMADDR = 0x40;
	
	/**
	 *	\var 	SETDDRAMADDR
	 * 	\brief	The DDRAM addressing selector command
	 * 	\value	0x80
	 */
	const static inline uint8_t SETDDRAMADDR = 0x80;
	
	/**
	 *	\var 	ENTRYRIGHT
	 * 	\brief	The command to specify the entry from the right side
	 * 	\value	0x00
	 */
	const static inline uint8_t ENTRYRIGHT = 0x00;
	
	/**
	 *	\var 	ENTRYLEFT
	 * 	\brief	The command to specify the entry from the left side
	 * 	\value	0x02
	 */
	const static inline uint8_t ENTRYLEFT = 0x02;
	
	/**
	 *	\var 	ENTYRSHIFTDECREMENT
	 * 	\brief	The command specifies the cursors shift behavior 
	 * 	\value	0x01
	 */
	const static inline uint8_t ENTRYSHIFTINCREMENT = 0x01;
	
	/**
	 *	\var 	ENTRYSHIFTDECREMENT
	 * 	\brief	The command specifies the cursors shift behavior
	 * 	\value	0x00
	 */
	const static inline uint8_t ENTRYSHIFTDECREMENT = 0x00;
	
	/**
	 *	\var 	DISPLAYON
	 * 	\brief	The command to activate the display
	 * 	\value	0x04
	 */
	const static inline uint8_t DISPLAYON = 0x04;
	
	/**
	 *	\var 	DISPLAYOFF
	 * 	\brief	The command to deactivate the display
	 * 	\value	0x00
	 */
	const static inline uint8_t DISPLAYOFF = 0x00;
	
	/**
	 *	\var 	CURSORON
	 * 	\brief	The command to activate the cursor
	 * 	\value	0x02
	 */
	const static inline uint8_t CURSORON = 0x02;
	
	/**
	 *	\var 	CURSOROFF
	 * 	\brief	The command to deactivate the cursor
	 * 	\value	0x00
	 */
	const static inline uint8_t CURSOROFF = 0x00;
	
	/**
	 *	\var 	BLINKON
	 * 	\brief	The command to activate displays blinking
	 * 	\value	0x01
	 */
	const static inline uint8_t BLINKON = 0x01;
	
	/**	
	 *	\var 	BLINKOFF
	 * 	\brief	The command to deactivate displays blinking
	 * 	\value	0x00
	 */
	const static inline uint8_t BLINKOFF = 0x00;
	
	/**
	 *	\var 	DISPLAYMOVE
	 * 	\brief	The command to move the display page
	 * 	\value	0x08
	 */
	const static inline uint8_t DISPLAYMOVE = 0x08;
	
	/**
	 *	\var 	CURSORMOVE
	 * 	\brief	The command to move the cursor
	 * 	\value	0x00
	 */
	const static inline uint8_t CURSORMOVE = 0x00;
	
	/**
	 *	\var 	MOVERIGHT
	 * 	\brief	The command to move to the right
	 * 	\value	0x04
	 */
	const static inline uint8_t MOVERIGHT = 0x04;
	
	/**
	 *	\var 	MOVELEFT
	 * 	\brief	The command to move to the left
	 * 	\value	0x00
	 */
	const static inline uint8_t MOVELEFT = 0x00;
	
	/**
	 *	\var 	MODE8BIT
	 * 	\brief	The command to select 8 bit mode
	 * 	\value	0x10
	 */
	const static inline uint8_t MODE8BIT = 0x10;
	
	/**
	 *	\var 	MODE4BIT
	 * 	\brief	The command to select 4 bit mode
	 * 	\value	0x00
	 */
	const static inline uint8_t MODE4BIT = 0x00;
	
	/**
	 *	\var 	MODE2LINE
	 * 	\brief	The command to select two line preset
	 * 	\value	0x08
	 */
	const static inline uint8_t MODE2LINE = 0x08;
	
	/**
	 *	\var 	MODE1LINE
	 * 	\brief	The command to select one line preset
	 * 	\value	0x00
	 */
	const static inline uint8_t MODE1LINE = 0x00;
	
	/**
	 *	\var 	MODE5x1DOTS
	 * 	\brief	The command to select 5x1DOT preset
	 * 	\value	0x04
	 */
	const static inline uint8_t MODE5x10DOTS = 0x04;
	
	/**
	 *	\var 	MODE5x8DOTS
	 * 	\brief	The command to select MODE5x8DOTS preset
	 * 	\value	0x00
	 */
	const static inline uint8_t MODE5x8DOTS = 0x00;
	
	/**
	 *	\var 	BACKLIGHT
	 * 	\brief	The command to enable backlighting
	 * 	\value	0x08
	 */
	const static inline uint8_t BACKLIGHT = 0x08;
	
	/**
	 *	\var 	NOBACKLIGHTING
	 * 	\brief	The command to disable backlight
	 * 	\value	0x00
	 */
	const static inline uint8_t NOBACKLIGHT = 0x00;
	
	/**
	 *	\var 	EN
	 * 	\brief	The bitmask for pulseEnable
	 * 	\value  0x04
	 */
	
	const static inline uint8_t EN = 0b00000100;
	
	/**
	 *	\var 	RW
	 * 	\brief	The bitmask to specify read/write access
	 * 	\value	0x02
	 */
	const static inline uint8_t RW = 0b00000010;
	
	/**
	 *	\var 	RS
	 * 	\brief	The bitmask to print character
	 * 	\value	0x01
	 */
	const static inline uint8_t RS = 0b00000001;
};

#endif //__LCD_HPP__