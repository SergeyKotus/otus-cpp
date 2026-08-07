#include <iostream>
#include <map>
#include "MyList.h"

long long factorial(int n)
{
    long long res = 1;
    for (int i = 1; i <= n; ++i)
    {
        res *= i;
    }
    return res;
}

template <typename T, std::size_t MAX_SIZE>
class MyAllocator
{
    size_t m_size = 0;
    T* m_buff = nullptr;

public:
    using value_type = T;
    template <class U> struct rebind
    {
        using other = MyAllocator<U, MAX_SIZE>;
    };

    MyAllocator()
    {
        m_buff = new T[MAX_SIZE];
    }

    ~MyAllocator()
    {
        delete[] m_buff;
    }

    //MyAllocator(const MyAllocator& other) = delete;
    MyAllocator(const MyAllocator&)
    {
        m_buff = new T[MAX_SIZE];
    }

    MyAllocator(MyAllocator&& other) noexcept
    {
        std::swap(m_size, other.m_size);
        std::swap(m_buff, other.m_buff);
    }

    MyAllocator& operator=(const MyAllocator& other) = delete;



    MyAllocator& operator=(MyAllocator&& other) noexcept
    {
        if(this != &other)
        {
            std::swap(m_size, other.m_size);
            std::swap(m_buff, other.m_buff);
        }
        return *this;
    }

    T* allocate(size_t n)
    {
        if(m_size + n > MAX_SIZE)
            throw std::bad_alloc();
        T* ptr = m_buff + m_size;
        m_size += n;
        return ptr;
    }

    void deallocate([[maybe_unused]] T* ptr, [[maybe_unused]] size_t n) noexcept
    {
    }

    template <class... Args> void construct(T* ptr, Args&&... args)
    {
        new (ptr) T(std::forward<Args>(args)...);
    }

    void destroy(T* ptr)
    {
        ptr->~T();
    }

    bool operator==(const MyAllocator&) const noexcept
    {std::cout << "operator ==  return true" << std::endl;
        return true;
    }

    bool operator!=(const MyAllocator&) const noexcept
    {std::cout << "operator !=  return false" << std::endl;
        return false;
    }
};



int main()
{
    std::map<int, int> stdMap;
    for(int i = 0; i < 10; ++i)
        stdMap[i] = factorial(i);

    std::cout << "std::map" << std::endl;
    for(const auto& value : stdMap)
        std::cout << value.first << " " << value.second << std::endl;
    std::cout << std::endl;

    std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>, 10>> stdMapA;
    for(int i = 0; i < 10; ++i)
        stdMapA[i] = factorial(i);

    std::cout << "std::map with MyAllocator" << std::endl;
    for(const auto& value : stdMapA)
        std::cout << value.first << " " << value.second << std::endl;
    std::cout << std::endl;

    MyList<int> myList;
    for(int i = 0; i < 10; ++i)
        myList.push_back(i);

    std::cout << "MyList" << std::endl;
    for(const auto& value : myList)
        std::cout << value << std::endl;
    std::cout << std::endl;

    MyList<int, MyAllocator<int, 11>> myListA;//11 - из-за хвостовой ноды в моем списке с курса Basic
    for(int i = 0; i < 10; ++i)
        myListA.push_back(i);

    std::cout << "MyList with MyAllocator" << std::endl;
    for(const auto& value : myListA)
        std::cout << value << std::endl;
    std::cout << std::endl;
    
    return 0;
}
