#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <sstream>
#include <cstdint>
#include "ip_pool_functions.h"


int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
    try
    {        
        IpPool ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            int int_ip[4];
            char dot;
            std::stringstream ss(line);
            ss >> int_ip[0] >> dot >> int_ip[1] >> dot >> int_ip[2] >> dot >> int_ip[3];
            ip_pool.push_back({static_cast<std::uint8_t>(int_ip[0]),
                               static_cast<std::uint8_t>(int_ip[1]),
                               static_cast<std::uint8_t>(int_ip[2]),
                               static_cast<std::uint8_t>(int_ip[3])});
        }

        // TODO reverse lexicographically sort                
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<IpPool::value_type>{});
        showIpPool(ip_pool.cbegin(), ip_pool.cend());
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        auto iter_range = filter(ip_pool, 1);
        showIpPool(iter_range.first, iter_range.second);
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        iter_range = filter(ip_pool, 46, 70);
        showIpPool(iter_range.first, iter_range.second);
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        showIpPool(ip_pool.cbegin(), ip_pool.cend(),
                   [](const auto& ip){return std::find(ip.cbegin(), ip.cend(), 46) != ip.cend();});
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
