#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <sstream>
#include <cstdint>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
//std::vector<std::string> split(const std::string &str, char d)
//{
//    std::vector<std::string> r;

//    std::string::size_type start = 0;
//    std::string::size_type stop = str.find_first_of(d);
//    while(stop != std::string::npos)
//    {
//        r.push_back(str.substr(start, stop - start));

//        start = stop + 1;
//        stop = str.find_first_of(d, start);
//    }

//    r.push_back(str.substr(start));

//    return r;
//}

void showIpPool(std::vector<std::array<uint8_t, 4>>::const_iterator first_it,
                std::vector<std::array<uint8_t, 4>>::const_iterator last_it,
                bool (*condition)(const std::array<uint8_t, 4>& ip) = nullptr)
{    
    for(auto it = first_it; it != last_it; ++it)
    {
        if((condition == nullptr) || condition(*it))
            std::cout << static_cast<int>((*it)[0]) << "." << static_cast<int>((*it)[1]) << "."
                      << static_cast<int>((*it)[2]) << "." << static_cast<int>((*it)[3]) << std::endl;
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
    try
    {        
        std::vector<std::array<uint8_t, 4>> ip_pool;

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
        auto compareIP = [](const auto& ip1, const auto& ip2){return ip1 > ip2;};
        std::sort(ip_pool.begin(), ip_pool.end(), compareIP);
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
//        auto filter_1 = [](const auto& ip){return ip[0] == 1;};
//        auto first_it = std::find_if(ip_pool.cbegin(), ip_pool.cend(), filter_1);
//        auto last_it = std::find_if_not(first_it, ip_pool.cend(), filter_1);        
        decltype(ip_pool)::value_type lb_1 = {1, 255, 255, 255};
        auto first_it = std::lower_bound(ip_pool.cbegin(), ip_pool.cend(), lb_1, compareIP);        
        decltype(ip_pool)::value_type ub_1 = {1, 0, 0, 0};
        auto last_it = std::upper_bound(first_it, ip_pool.cend(), ub_1, compareIP);
        showIpPool(first_it, last_it);
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
//        auto filter_46_70 = [](const auto& ip){return ip[0] == 46 && ip[1] == 70;};
//        first_it = std::find_if(ip_pool.cbegin(), ip_pool.cend(), filter_46_70);
//        last_it = std::find_if_not(first_it, ip_pool.cend(), filter_46_70);
        decltype(ip_pool)::value_type lb_46_70 = {46, 70, 255, 255};
        first_it = std::lower_bound(ip_pool.cbegin(), ip_pool.cend(), lb_46_70, compareIP);
        decltype(ip_pool)::value_type ub_46_70 = {46, 70, 0, 0};
        last_it = std::upper_bound(first_it, ip_pool.cend(), ub_46_70, compareIP);
        showIpPool(first_it, last_it);
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
