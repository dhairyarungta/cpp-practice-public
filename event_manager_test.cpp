#include "event_manager.h"
#include <iostream>

void callback1(int num)
{
    std::cout<<"\n";
    std::cout<<"callback1-"<<num*2;

}

void callback2(int num)
{
    std::cout<<"\n";

}

int main()
{
    EventManager* event_manager = new EventManager();
    event_manager->on("event", callback1)->on("event", callback2);
    int eventA = event_manager->emit("event", 100);
    int eventB = event_manager->emit("bad_event", 200);

    std::cout<<"\n";
    std::cout<<eventA<<" "<<eventB<<std::endl;
    return 0;
}