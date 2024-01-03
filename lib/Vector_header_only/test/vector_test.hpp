#include "../vector.hpp"

/**
 *  \test   assignmentTest
 *  \brief  Bytes are stored in vector and displayed
 */
void assignmentTest(void)
{
    constexpr uint8_t byte0 = 10;
    constexpr uint8_t byte1 = 10;
    constexpr uint8_t byte2 = 20;
    constexpr uint8_t byte3 = 30;
    constexpr uint8_t byte4 = 40;
    
    constexpr vector<uint8_t> numbers;
    numbers.append(byte0);
    numbers.append(byte1);
    numbers.append(byte2);
    numbers.append(byte3);
    numbers.append(byte4);

    assert(byte0 == numbers.at(0));
    assert(byte1 == numbers.at(1));
    assert(byte2 == numbers.at(2));
    assert(byte3 == numbers.at(3));
    assert(byte4 == numbers.at(4));
}
