
#include <iostream>
#include <thread>
#include <pthread.h>
#include "threadLocal.h"

using namespace std;
int errorcount=0;

cop5618::threadLocal <int> ob;

std::mutex lock_errCount;

void sg(int a)                                                              //attempting set before get
{
   try
   {
        ob.set(a);
   //std::mutex lock_map;
        const int c=ob.get();                                               //get() returns value associated with key
        cout<<"\nItem retrieved "<<std::this_thread::get_id()<<":"<<c;        //printing ID of current thread
   }
   catch (const char* errorMsg)
   {
        std::lock_guard<std::mutex> lock(lock_errCount);
        errorcount++;
        cout << errorMsg << endl;

   }

}

void gs(int a)                                                          //attempting get before set
{
    try
    {
        ob.get();
        ob.set(a);
    }
    catch (const char* errorMsg)
    {

      std::lock_guard<std::mutex> lock(lock_errCount);
      errorcount++;
      cout << errorMsg << endl;
    }
}


void rr()                                                                      //attempting consecutive remove
{
    try
    {
        ob.remove();
        ob.remove();
    }
    catch (const char* errorMsg)
    {
        std::lock_guard<std::mutex> lock(lock_errCount);
        errorcount++;
       cout << errorMsg << endl;

    }
}

void rg()                                                                    //attempting remove and then get
{
    try
    {
        ob.remove();
        const int value=ob.get();
    }
    catch (const char* errorMsg)
     {
        std::lock_guard<std::mutex> lock(lock_errCount);
        errorcount++;
        cout << errorMsg << endl;

     }
}

void ss(int a)                                                        //Attempting consecutive sets
{
    try
    {
    ob.set(a);
    ob.set(a);
    }
    catch (const char* errorMsg)
    {
        std::lock_guard<std::mutex> lock(lock_errCount);
        errorcount++;
       cout << errorMsg << endl;

    }
}

void setonly(int a)
{
    ob.set(a);
}

void getonly()
{
    try
    {
        const int value=ob.get();
    }

    catch (const char* errorMsg)
     {
        std::lock_guard<std::mutex> lock(lock_errCount);
        errorcount++;
        cout << errorMsg << endl;

     }
}


void removefirst()
{
    try
    {
        ob.remove();
    }

    catch (const char* errorMsg)
     {
        std::lock_guard<std::mutex> lock(lock_errCount);
        errorcount++;
        cout << errorMsg << endl;

     }
}

int test_threadLocal()
{                                                                       //Spawning threads
         //std::thread a(gs), b(sg),c(gg);
    std::thread t1(sg,5),t2(gs,10),t3(rr),t4(sg,67),t5(rg),t6(ss,25),t7(setonly,125),t8(getonly), t9(removefirst);


    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();

    //cout<<"error"<<errorcount;
    return errorcount;
}


