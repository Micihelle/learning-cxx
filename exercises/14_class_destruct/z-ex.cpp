#include <iostream>
 
struct A
{
    int i;
 
    A(int num) : i(num)
    {
        std::cout << "构造 a" << i << '\n';
    }
 
    ~A() //显式定义析构函数
    {
        std::cout << "析构 a" << i << '\n';
    }
};
 
A a0(0);  //全局变量 a0 是一个静态对象。 传参打印->"构造a0"
 
int main()
{
    A a1(1);
    A* p;
 
    { // 嵌套的作用域
        A a2(2);
        p = new A(3);
    } // a2 离开作用域 (为什么离开作用域之后会自觉析构函数呢？跟此前的结构体声明有什么关系呢？只要离开作用域就直接调用相应的析构函数？)
 
    delete p; // 调用 a3 的析构函数
}