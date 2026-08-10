#include <iostream>
#include <algorithm>
#include "ip_pool_functions.h"


void showIpPool(IpPool::const_iterator first_it, IpPool::const_iterator last_it, bool (*condition)(const IpPool::value_type& ip))
{
    for(auto it = first_it; it != last_it; ++it)
    {
        if((condition == nullptr) || condition(*it))
            std::cout << static_cast<int>((*it)[0]) << "." << static_cast<int>((*it)[1]) << "."
                      << static_cast<int>((*it)[2]) << "." << static_cast<int>((*it)[3]) << std::endl;
    }
}

template <typename ...Args>
std::pair<IpPool::const_iterator, IpPool::const_iterator> filter(const IpPool& ip_pool, Args... ip)
{
    static_assert((sizeof...(ip) <= 4), "invalid number of parameters");
    IpPool::value_type lb = {255, 255, 255, 255};
    IpPool::value_type ub = {0, 0, 0, 0};
    const uint8_t ip_parts[] = {static_cast<uint8_t>(ip)...};
    for(std::size_t i = 0; i < sizeof... (ip); ++i)
    {
        lb[i] = ip_parts[i];
        ub[i] = ip_parts[i];
    }

    IpPool::const_iterator first_it = std::lower_bound(ip_pool.cbegin(), ip_pool.cend(), lb, std::greater<IpPool::value_type>{});
    if(first_it != ip_pool.cend())
    {
        IpPool::const_iterator last_it = std::upper_bound(ip_pool.cbegin(), ip_pool.cend(), ub, std::greater<IpPool::value_type>{});
        return std::make_pair(first_it, last_it);
    }
    return std::make_pair(first_it, ip_pool.cend());
}

template std::pair<IpPool::const_iterator, IpPool::const_iterator> filter<int>(const IpPool&, int);
template std::pair<IpPool::const_iterator, IpPool::const_iterator> filter<int, int>(const IpPool&, int, int);
