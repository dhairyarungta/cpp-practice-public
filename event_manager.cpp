#ifndef EVENT_MANAGER
#define EVENT_MANAGER

#include <algorithm>
#include <vector>
#include <map>

class EvntManager
{
private :
    std::map<std::string, std::vector<void(*)(int)> > events;
    
public :

    EventManager(){}
    EventManager* on(std::string event_name, void(*callback)(int))
    {

    }
}

#endif