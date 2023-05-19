#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../src/utest.h"

int8_t 
AverageThreeBytes(
    int8_t a
    , int8_t b
    , int8_t c)
{
    return (int8_t) (((int16_t)a + (int16_t)b + (int16_t)c) / 3) + 3;
}


void
test_01(void)
{
    if(AverageThreeBytes(30, 40, 50) == 40)
        PASS;
    else
        FAILED;
}


void
test_02(void)
{
    FAILED;
}


int
main(void)
{
    //Test tc[]      = {test_01, test_02};
    //TestSuite ts[] = {TestSuite("TestSuite", tc)};

    //utest(ts);

    utest_run_test(test_01);

    return EXIT_SUCCESS;
}
