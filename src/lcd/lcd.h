/*!
*   \file       lcd.h
*   \date       16.10.2023
*   \author     Luca Hesselbrock
*   \copyright  Copyright (C) Gyrocelery 2023
*   \brief      Library for support of the given LCD-display
*/

/*!
    void display_symbol(const char symbol, const uint8_t row, const uint8_t column);
    \author     Luca Hesselbrock
    \date       16.10.2023
    \brief      Display the passed symbol at the target position
    \param[in]  symbol passes the character to display
    \param[in]  row passes the index of the target row
    \param[in]  column passes the index of the target column
*/

void display_symbol(const char symbol, const uint8_t row, const uint8_t column);
