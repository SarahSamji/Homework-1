#include <iostream>
#include "threadLocal.h"
//#include "threadLocal_test.cpp"
#include <thread>

using namespace std;


int test_threadLocal();

int main()
{
    int err = test_threadLocal();
    return err;
}
