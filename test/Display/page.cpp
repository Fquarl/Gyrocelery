#include "page.h"

#include <cassert>

/* Predefinitions */

/**
 *  \test    REPRESENTATION_TEST
 *  \brief   The test validates the represantation of ASCII characters 
 */
void REPRESENTATION_TEST(void)
{
    constexpr char* testString = "This is a test!\n\r_*";
    constexpr int stringLength = sizeof(testString) / sizeof(char);
    Page testPage(testString);

    for (int i = 0; i < stringLength; i++)
    {
        assert((void("REPRESENTATION_TEST FAILED"), testPage[i]==testString[i]));
    }
}
