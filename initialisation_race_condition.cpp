#include <bits/stdc++.h>
using namespace std;


int main(){
}

std::shared_ptr<some_resource>resource_ptr;
std::once_flag resource_flag;

void init_resource()
{
    resource_ptr.reset(new some_resource);
}

void foo()
{
    std::call_once(resource_flag, init_resource);
    resource_ptr->do_something();

}

