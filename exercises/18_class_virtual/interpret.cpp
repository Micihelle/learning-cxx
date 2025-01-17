#include <iostream>
 
struct Base
{
    virtual void f()   
    // virtual 声明-告诉编译器：在调用这个函数时，应该根据实际对象的类型来决定调用哪个版本的函数。这就是所谓的动态绑定
    // void f()为虚函数，C++ 会通过对象的虚表（VTable）来查找正确的函数地址。
    {
        std::cout << "基\n";
    }
};
 
struct Derived : Base
{
    void f() override // 'override' 可选
    {
        std::cout << "派生\n";
    }
};
 
int main()
{
    Base b;
    Derived d;
    b.f();
    d.f();
    // 通过引用调用虚函数 (运行时多态：通过基类引用或指针，调用派生类的重写方法)
    // 运行时多态：通过基类引用调用虚函数时，C++ 会查找对象的实际类型，然后调用相应派生类中的函数。
    Base& br = b; // br 的类型是 Base&  （我怎么知道他指向的是基类对象还是派生类对象？）（这里引用的是基类对象）
                  // 将基类引用br 绑定到基类对象b上
    Base& dr = d; // dr 的类型也是 Base& (明明是相同类型，为什么说他是引用派生类对象)
    br.f(); // 打印 "基"
    dr.f(); // 打印 "派生"
 
    // 通过指针调用虚函数
    Base* bp = &b; // bp 的类型是 Base*  （指向基类对象还是派生类对象？为什么类型相同但是能够指向不同对象，好像是个很显然的问题）
    Base* dp = &d; // dp 的类型也是 Base*
    bp->f(); // 打印 "基"
    dp->f(); // 打印 "派生"
 
    // 非虚函数调用（显式调用）
    br.Base::f(); // 打印 "基"
    dr.Base::f(); // 打印 "基"
}