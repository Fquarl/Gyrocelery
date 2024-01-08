/**
 *  \file lcd.cpp
 */

#include "lcd.hpp"

LCD::LCD(void)
{
	init();
}

void LCD::printFormatted(const Vector<char>& text)
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


void LCD::print(char text[32])
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

void LCD::home(void)
{
	command(RETURNHOME);
	_delay_us(2000);
}

void LCD::clear(void)
{
	command(CLEARDISPLAY);
	_delay_us(2000);
}

void LCD::setCursor(const uint8_t& columnIndex, const uint8_t& rowIndex)
{
	const uint8_t rowOffsets[] = {0x00, 0x40, 0x14, 0x54};
	uint8_t rowIndexVolatile = rowIndex;
	if (rowIndexVolatile > _rowCount)
	{
		rowIndexVolatile = _rowCount - 1;
	}
	command(SETDDRAMADDR | (columnIndex + rowOffsets[rowIndexVolatile]));
}

void LCD::backlightOnOff(const bool& state)
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

void LCD::blinkOnOff(const bool& state)
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

void LCD::cursorOnOff(const bool& state)
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

void LCD::displayOnOff(const bool& state)
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

void LCD::init(void)
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

void LCD::sendAddress(void)
{
    TWDR = _lcdAddress;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    while ((TWSR & 0xF8) != 0x18);
}

void LCD::expanderWrite(const uint8_t& value)
{
    i2c_startCondition();
    sendAddress();
    i2c_sendData(value | _backlightValue);
    i2c_stopCondition();
}

void LCD::pulseEnable(const uint8_t& value)
{
    expanderWrite(value | EN);
    _delay_us(1);
    expanderWrite(value & ~EN);
    _delay_us(50);
}

void LCD::write4bits(const uint8_t& value)
{
    expanderWrite(value);
    pulseEnable(value);
}

void LCD::send(const uint8_t& value, const uint8_t& mode)
{
    uint8_t highnib = value & 0xf0;
    uint8_t lownib = (value << 4) & 0xf0;
    write4bits((highnib) | mode);
    write4bits((lownib) | mode);
}

void LCD::command(const uint8_t& value)
{
    send(value, 0);
}

void LCD::leftToRight(void)
{
	_displayMode |= ENTRYLEFT;
	command(ENTRYMODESET | _displayMode);
}

void LCD::rightToLeft(void)
{
	_displayMode &= ~ENTRYLEFT;
	command(ENTRYMODESET | _displayMode);
}

void LCD::scrollDisplayLeft(void)
{
	command(CURSORSHIFT | DISPLAYMOVE | MOVELEFT);
}

void LCD::scrollDisplayRight(void)
{
	command(CURSORSHIFT | DISPLAYMOVE | MOVERIGHT);
}

void LCD::leftJustify(void)
{
	_displayMode &= ~ENTRYSHIFTINCREMENT;
	command(ENTRYMODESET | _displayMode);
}

void LCD::rightJustify(void)
{
	_displayMode |= ENTRYSHIFTINCREMENT;
	command(ENTRYMODESET | _displayMode);
}

void LCD::enter4bitMode(void)
{
	write4bits(0x03 << 4);
	_delay_us(4500);
	write4bits(0x03 << 4);
	_delay_us(4500);
	write4bits(0x03 << 4);
	_delay_us(150);
	write4bits(0x02 << 4);
}