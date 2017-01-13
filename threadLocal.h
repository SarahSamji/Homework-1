#ifndef THREADLOCAL_H_
#define THREADLOCAL_H_

#include <iostream>
#include <thread>
#include<iterator>
#include <mutex>
#include <unordered_map>

using namespace std;
std::mutex lock_map;                                //declaring a mutex variable lock_map to lock the map

namespace cop5618 {

template <typename T>
class threadLocal {

public:

threadLocal()=default;

threadLocal(const threadLocal&)=delete;
threadLocal& operator=(const threadLocal&)=delete;
threadLocal(threadLocal&&)=delete;
threadLocal& operator=(const threadLocal&&)=delete;


const T& get() const;



void set(T val);


void remove();


~threadLocal()=default;
//std::unordered_map<std::string,double>::const_iterator got = mymap.find (input);
template <typename U>
friend std::ostream& operator<< (std::ostream& os, const threadLocal<U>& obj);
/*{
    for( it = thread_value_map.begin(); it != thread_value_map.end(); ++it)
    os<< it->first << " " << it->second<< "\n";
}*/
 private:
std::unordered_map <std::thread::id, T> thread_value_map;
};                                                                      //Definitions for the get(),set(), remove()

template <typename T>
const T& threadLocal<T> ::  get() const
{

    std::lock_guard<std::mutex> lock(lock_map);
    //try
   // {
        if(thread_value_map.find(std::this_thread::get_id()) == thread_value_map.end())                     //Searching the map to see if there is an entry for current thread
    {
       throw "\nAttempting to get a value before setting";
    }
   else {
        return thread_value_map.find(std::this_thread::get_id())->second;                       //If present return the value
    }
    //}
    /*catch( const char* msg)
    {
        cerr<<msg<<endl;

    }*/
}

template <typename T>
void threadLocal<T> :: set(T val)
{
     std::lock_guard<std::mutex> lock(lock_map);

   thread_value_map.emplace(std::this_thread::get_id(),val);                        //Associating current thread ID and value

}


template <typename T>
void threadLocal<T> :: remove()
{
   // try{
        if(thread_value_map.find(std::this_thread::get_id()) == thread_value_map.end())
        {
        //cout<<"Thread is not in the map!";

            throw "\nAttempting to remove a non-existing element";
        }

    else {
             std::lock_guard<std::mutex> lock(lock_map);
            thread_value_map.erase(std::this_thread::get_id());
        }
       // }
     /*   catch(const char* msg)
    {
        cerr<<msg<<endl;
    }*/
    }
} /* namespace cop5618 */
#endif /* THREADLOCAL_H_ */
