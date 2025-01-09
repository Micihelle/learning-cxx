#include <cstdint>
#include <iostream>
 
// 采用 16 位的枚举
enum smallenum: std::int16_t
{
    a,
    b,
    c
};
 
// color 可以是 red（值为 0）、yellow（值为 1）、green（值为 20）或 blue（值为 21）
enum color
{
    red,
    yellow,
    green = 20,
    blue
};
 
// altitude 可为 altitude::high 或 altitude::low
enum class altitude: char
{ 
    high = 'h',
    low = 'l', // CWG 518 之后才允许尾部的逗号
}; 
 
// 常量 d 为 0，常量 e 为 1，常量 f 为 3
enum
{
    d,
    e,
    f = e + 2
};
 
// 枚举类型（有作用域和无作用域）能有重载的运算符
std::ostream& operator<<(std::ostream& os, color c)
{
    switch(c)
    {
        case red   : os << "红"; break;
        case yellow: os << "黄"; break;
        case green : os << "绿"; break;
        case blue  : os << "蓝"; break;
        default    : os.setstate(std::ios_base::failbit);
    }
    return os;
}
 
std::ostream& operator<<(std::ostream& os, altitude al)
{
    return os << static_cast<char>(al);
}
 
// 有作用域枚举（C++11）能部分地在早期 C++ 版本模拟：
 
enum struct E11 { x, y }; // C++11 起
 
struct E98 { enum { x, y }; }; // C++11 前也 OK
 
namespace N98 { enum { x, y }; } // C++11 前也 OK
 
struct S98 { static const int x = 0, y = 1; }; // C++11 前也 OK
 
void emu()
{
    std::cout << (static_cast<int>(E11::y) + E98::y + N98::y + S98::y) << '\n'; // 4
}
 
namespace cxx20
{
    enum class long_long_long_name { x, y };
 
    void using_enum_demo()
    {
        std::cout << "C++20 `using enum`：__cpp_using_enum == ";
        switch (auto rnd = []{return long_long_long_name::x;}; rnd())
        {
#if defined(__cpp_using_enum)
            using enum long_long_long_name;
            case x: std::cout << __cpp_using_enum << "；x\n"; break;
            case y: std::cout << __cpp_using_enum << "；y\n"; break;
#else
            case long_long_long_name::x: std::cout << "？；x\n"; break;
            case long_long_long_name::y: std::cout << "？；y\n"; break;
#endif
        }
    }
}
 
int main()
{
    color col = red;
    altitude a;
    a = altitude::low;
 
    std::cout << "col = " << col << '\n'
              << "a = "   << a   << '\n'
              << "f = "   << f   << '\n';
 
    cxx20::using_enum_demo();
}


// READ: 枚举类型 <https://zh.cppreference.com/w/cpp/language/enum>

/*
Output:
col = 红
a = l 
f = 3  //  line 29 匿名枚举 全局作用域，这应该就是题目里面所提到的污染命名空间
C++20 `using enum`：__cpp_using_enum == 201907；x
*/