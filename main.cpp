#include "pool.hpp"
#include <iostream>

int main()
{
    Pool<int> pool;

    pool.resize(10);

    Pool<int>::Object a = pool.acquire();

    std::cout << a.data << std::endl;
}