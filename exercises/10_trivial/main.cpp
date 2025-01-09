#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

// TODO: 实现正确的缓存优化斐波那契计算
// &cache 表示对 FibonacciCache fib的引用传递（直接对原始缓存进行操作）
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    for (int cached = 2; cached <= i; ++cached) {
        cache.cache[cached] = cache.cache[cached - 1] + cache.cache[cached - 2];  
    }
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // cache[0]=1;cache[1]=1;cache[2]=..;
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    FibonacciCache fib={{0,1},2};
    //std::cout << "fibonacci(10) == " << fibonacci(fib, 10) << std::endl;
    //std::cout << "fibonacci(9) == " << fibonacci(fib, 9) << std::endl;
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}

