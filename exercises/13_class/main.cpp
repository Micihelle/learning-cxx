#include "../exercise.h"

// C++ 中，`class` 和 `struct` 之间的**唯一区别**是
// `class` 默认访问控制符是 `private`，
// `struct` 默认访问控制符是 `public`。
// 以关键词 class 定义的类，它的成员和基类默认具有私有访问。
// 以关键词 struct 定义的类，它的成员和基类默认具有公开访问。
// union 的成员默认具有公开访问。

// READ: 访问说明符 <https://zh.cppreference.com/w/cpp/language/access>

// 这个 class 中的字段被 private 修饰，只能在 class 内部访问。
// 因此必须提供构造器来初始化字段。
// READ: 构造器 <https://zh.cppreference.com/w/cpp/language/constructor>
class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // TODO: 实现构造器
    // Fibonacci()
    // disc-> Fibonacci(): cache(0,1) {}
    Fibonacci(): cache{0,1} {}
    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        for (cached = 2; cached<=i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 现在类型拥有无参构造器，声明时会直接调用。
    // 这个写法不再是未定义行为了。
    Fibonacci fib;
    //std::cout << "DEBUG:fibonacci(10) = " << fib.get(10) << std::endl;
    //std::cout << "DEBUG:fibonacci(9) = " << fib.get(9) << std::endl;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
