#include <stdio.h>
#include <stdlib.h>
#include "except.h"

#define TEST_SUCCESS            1
#define TEST_FAILED             0

#define TRY_SUCCESS             0
#define FIRST_EXCEPTION_HANDLE  1
#define SECOND_EXCEPTION_HANDLE 2
#define RAISE_TO_ELSE           3

static Except_T First_Exception = {"first exception"};
static Except_T Second_Exception = {"second exception"};
static Except_T Unknown_Exception = {"unknown exception"};

void test_try(int *test_result)
{
    TRY
        *test_result = TEST_SUCCESS;
    ELSE
        RERAISE;
    END_TRY;
}

int main()
{
    int test_result = TEST_FAILED;

    printf("TRY test");
    test_try(&test_result);
    if(test_result == TEST_SUCCESS)
        printf("\tpassed!\n");
    else
        printf("\tfailed!\n");
    test_result = TEST_FAILED;

#if 0
    printf("First EXCEPTION test \n");
    test_except(try_success);
    if(test_result == TEST_SUCCESS)
        printf("\tpassed!\n");
    else
        printf("\tfailed\n");
    test_result = TEST_FAILED;

    printf("Second EXCEPTION test \n");
    test_except(try_success);
    if(test_result == TEST_SUCCESS)
        printf("\tpassed!\n");
    else
        printf("\tfailed\n");
    test_result = TEST_FAILED;


    printf("ELSE test\n");
    if(test_result == TEST_SUCCESS)
        printf("\tpassed!\n");
    else
        printf("\tfailed\n");
    test_except(try_success);
#endif

    return 0;
}
