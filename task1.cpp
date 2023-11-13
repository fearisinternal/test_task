#include <iostream>

void print_binary(const int64_t &n)
{
    const size_t byte_size = 8;
    for (int i = sizeof(n) * byte_size - 1; i >= 0; --i)
    {
        std::cout << (n >> i & 1);
    }
    std::cout << std::endl;
}

int main()
{
    print_binary(-1234567890);
    return 0;
}