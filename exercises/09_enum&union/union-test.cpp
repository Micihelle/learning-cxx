#include <cstdint>
#include <iostream>
 
union S
{
    std::int32_t n;     // 占用 4 字节
    std::uint16_t s[2]; // 占用 4 字节
    std::uint8_t c;     // 占用 1 字节
};                      // 整个联合体占用 4 字节
 
int main()
{
    S s = {0x12345678}; // 初始化首个成员，s.n 现在是活跃成员
    // 于此点，从 s.s 或 s.c 读取是未定义行为
    std::cout << std::hex << "s.n = " << s.n << '\n';
    s.s[0] = 0x0011; // s.s 现在是活跃成员
    // 在此点，从 n 或 c 读取是 UB 但大多数编译器都对其有定义
    std::cout << "s.c 现在是 " << +s.c << '\n' // 11 或 00，取决于平台 ->利用该特性可以判断采用的是大端系统还是小端系统
              << "s.n 现在是 " << s.n << '\n'; // 12340011 或 00115678
}