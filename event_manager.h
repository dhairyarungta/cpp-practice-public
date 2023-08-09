#ifndef EVENT_MANAGER
#define EVENT_MANAGER

#include <algorithm>
#include <vector>
#include <map>
#include <string>

class EventManager
{
private :
    std::map<std::string, std::vector<void(*)(int)> > events;
    
public :

    EventManager(){}
    EventManager* on(std::string event_name, void(*callback)(int))
    {
        std::vector<void(*)(int)> *listeners = &events[event_name];
        if(std::find(listeners->begin(), listeners->end(), callback)!=listeners->end())
        {
            return this;
        }

        listeners->push_back(callback);
        return this;
    }

    bool emit (std::string event_name, int arg)
    {
        std::vector<void(*)(int)>listeners = events[event_name];
        if(listeners.size()==0)
            return false;

        for (int idx = 0;idx<listeners.size();idx++)
        {
            listeners[idx](arg);
        }
        return true;
    }

};



#endif