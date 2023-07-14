
#include <bits/stdc++.h>
using namespace std;


int main(){
}

//thread safe lazy initilization
std::shared_ptr<some_resource> resource_ptr;
std:mutex resource_mutex;
void foo()
{
    std::unqiue_lock<std::mutex> lk(resrouter_mutex);
    if(!resouce_ptr)
    {
        resource_ptr.reset(new some_resource);
    }
    lk.unlock();
    resource_ptr->do_something();

}
//the above codes casues unncessary thread serialization leading
// reduceded perfomance advantage from multithreading 





void undefined_behaviour_with_double_checked_locking()
{
    if(!resource_ptr)
    {
        std::lock_guard<std::mutex> lk(resource_mutex );
        if(!resource_ptr)
        {
            resource_ptr.reset(new some_resouce);

        }
    }

    resource_ptr->do_soemthing();

}

