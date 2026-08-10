#ifndef IP_POOL_FUNCTION_H
#define IP_POOL_FUNCTION_H
#include <vector>
#include <array>
#include <cstdint>


using IpPool = std::vector<std::array<uint8_t, 4>>;

void showIpPool(IpPool::const_iterator first_it, IpPool::const_iterator last_it, bool (*condition)(const IpPool::value_type& ip) = nullptr);

template <typename ...Args>
std::pair<IpPool::const_iterator, IpPool::const_iterator> filter(const IpPool& ip_pool, Args... ip);

#endif // IP_POOL_FUNCTION_H
