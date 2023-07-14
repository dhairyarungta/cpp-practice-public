#include <bits/stdc++.h>
using namespace std;


int main(){
}

class some_big_object;
void swap(some_big_object &lhs, some_big_object& rhs);
class X
{
private :
    some_big_object some_detail;
    std::mutex m;



public :
    X (some_big_object const &sd ):some_detail(sd){}
    friend void swap(X& lhs, X& rhs)
    {
        if(&lhs==&rhs)
            return ;
        
        std::lock(lhs.m, rhs.m);
        std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
        std::lock_guard<std::mutex? lock_b(rhs.m, std::adopt_lock);
        swap(lhs.some_detail, rhs.some_detail);
    }
}

std::unique_lock<std::mutex> get_lock()
{
    extern std::mutex some_mutex;
    std::unique_lock<std::mutex> lk(some_mutex);
    prepare_data();
    return lk;

}
void process_data()
{
    std::unique_lock<std::mutex> lk(get_lock());
    do_something();
}

void get_and_process_data()
{
    std::unique_lock<std::mutex> my_lock(the_mutex);
    some_class data_to_process = get_next_chunk();
    my_lock.unlock();
    result_type result = process(data_to_process);
    my_lock.lock();
    write_result(data_to_process, result);
    
}