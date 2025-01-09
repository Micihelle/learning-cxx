#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        for (int cached = 2; cached<=i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    Fibonacci fib={{0,1},2};
    //std::cout << "DEBUG::fibonacci(90000000000) = " << fib.get(90000000000) << std::endl;
    //std::cout << "DEBUG::fibonacci(90) = " << fib.get(90) << std::endl;
    //std::cout << "DEBUG::fibonacci(10) = " << fib.get(10) << std::endl;
    //std::cout << "DEBUG::fibonacci(9) = " << fib.get(9) << std::endl;

    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
