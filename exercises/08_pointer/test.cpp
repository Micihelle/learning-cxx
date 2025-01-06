#include <iostream>
#include <iterator>
#include <numeric>
 
void g(int (&a)[3])
{
    std::cout << a[0] << '\n';
}
 
void f(int* p)
{
    std::cout << *p << '\n';
}
 
int main()
{
    int a[3] = {1, 2, 3};
    int* p = a; // 初始化指针 p，使其指向数组的首元素
 
    std::cout << sizeof a << '\n'  // 打印数组的大小
              << sizeof p << '\n'; // 打印指针的大小
 
    // 在可接受数组而不可接受指针的地方，只能使用数组
    g(a); // OK：函数以引用接受数组
//  g(p); // 错误
 
    for(int n: a)              // OK：数组可用于范围 for 循环
        std::cout << n << ' '; // 打印数组的各个元素
//  for(int n: p)              // 错误
//      std::cout << n << ' ';
 
    std::iota(std::begin(a), std::end(a), 7); // OK：begin 与 end 接受数组  数组 a 变为 {7, 8, 9}。（iterators)
//  std::iota(std::begin(p), std::end(p), 7); // 错误
 
    // 在可接受指针而不可接受数组处的地方，两者都可以使用
    f(a); // OK：函数接受指针     数组退化成指针：数组名 a 自动转换为指向数组首元素的指针，所以传递合法。
    f(p); // OK：函数接受指针  指向a[]的元素
    std::cout << *a << '\n' // 打印首元素
              << *p << '\n' // 相同
              << *(a + 1) << ' ' << a[1] << '\n'  // 打印第二元素
              << *(p + 1) << ' ' << p[1] << '\n'; // 相同
}

// Output:
/*
12
8
1
1 2 3 7
7
7
7
8 8
8 8
*/