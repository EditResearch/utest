#include "utest.h"

#include <signal.h>
#include <stdio.h>


Exception __exception__;


#define try \
    if((__exception__.exp = setjmp(__exception__.env)) == Test_Pass)


#define catch(T) \
    else if(__exception__.exp == (T))


#define finally \
    else


static void 
__sigsegv_handler__(int signum)
{
    (void) signum;
    throw(Test_Fatal);
}   


__attribute__((constructor))
static void
__init__()
{
    signal(SIGSEGV, __sigsegv_handler__);
}


static inline void
__run_test_suite__(TestSuite ts)
{
    for(size_t j = 0; j < ts.length; j++)
        utest_run_test(ts.tc[j]);
}


void
utest_run(
    size_t length
    , TestSuite * ts)
{
    for(size_t i = 0; i < length; i++)
    {
        printf("-------- %s\n", ts[i].name);
        __run_test_suite__(ts[i]);
    }
}


void
utest_run_test(Test test)
{
    try
    {
        test();
        fprintf(stdout, "%s:%s: [PASSED]\n", __exception__.file, __exception__.func);
    }
    catch(Test_Fail)
    {
        fprintf(stderr, "%s:%s:%zu: [FAILED]\n"
            , __exception__.file
            , __exception__.func
            , __exception__.line);
    }
    catch(Test_Fatal)
    {
        fprintf(
            stderr
            , "%s:%s:%zu: [FATAL]\n"
            , __exception__.file
            , __exception__.func
            , __exception__.line);
    }
    finally
    {
        fprintf(
            stderr
            , "%s:%s:%zu: Unknown exception: %ld\n"
            , __exception__.file
            , __exception__.func
            , __exception__.line
            , __exception__.exp);

        return;
    }
}
