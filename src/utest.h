#ifndef _UTEST_H_
#define _UTEST_H_

#include <stddef.h>
#include <setjmp.h>


typedef struct
{
    jmp_buf env;

    long exp;
    size_t line;
    const char * file;
    const char * func;
}Exception;


extern Exception __exception__;


typedef enum
{
    Test_Pass 
    , Test_Fail
    , Test_Fatal    
}TestResult;


#define throw(T)                            \
    do                                      \
    {                                       \
        __exception__.line = __LINE__;      \
        __exception__.file = __FILE__;      \
        __exception__.func = __func__;      \
                                            \
        longjmp(__exception__.env, T);      \
    }while(0)


#define PASS                                \
    do                                      \
    {                                       \
        __exception__.file = __FILE__;      \
        __exception__.func = __func__;      \
        return;                             \
    }while(0)                               


#define FAILED          \
    throw(Test_Fail)    


#define FATAL           \
    throw(Test_Fatal)   


typedef void(*Test)(void);


typedef struct
{
    const char * name;

    size_t length;
    Test * tc;
}TestSuite;


#define TestSuite(name, tc)                 \
    (TestSuite)                             \
    {                                       \
        (name)                              \
        , (sizeof((tc)) / sizeof(*(tc)))    \
        , (tc)                              \
    }


void
utest_run(
    size_t length
    , TestSuite * ts);


#define utest(ts) \
    utest_run(sizeof((ts)) / sizeof(*(ts)), (ts))


void
utest_run_test(Test test);


#endif



