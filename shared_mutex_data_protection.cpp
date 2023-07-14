#include <bits/stdc++.h>

class dns_entry;
class dns_cache
{
    std::map<std::string, dns_entry> entries;
    mutable boost::shared_mutex entry_mutex;

public:
    dns_entry find_entry(std::string const& domain) const 
    {
        boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
        auto it = entries.find(domain); //it is of type iterator on the map
        return (it==entries.end())?dns_entry():it->second;


    }

    void update_or_add_entry(std::string const& domain, dns_entry const& dns_details)
    {
        std::lock_guard<boost::shared_mutex> lk(entry_mutex);
        entries[domain] = dns_details;
    }
};