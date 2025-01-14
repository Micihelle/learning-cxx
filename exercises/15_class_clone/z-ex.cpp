struct A
{
    int n;
    A(int n = 1) : n(n) {}
    A(const A& a) : n(a.n) {} // 用户定义的复制构造函数;在用同类型对象构造新对象时被调用，例如：A a2(a1)
};
 
struct B : A   // B 是 A 的派生类，它继承了 A 的所有公开成员（包括构造函数和方法）。
{
    // 隐式默认构造函数 B::B()   会自动调用 A 的默认构造函数。
    // 隐式复制构造函数 B::B(const B&)  调用 A 的复制构造函数以初始化 A 的部分。
};
 
struct C : B
{
    C() : B() {}
private:
    C(const C&); // 不可复制，C++98 风格 自定义复制构造函数且设为 private，因此无法复制 C 类型的对象。
};
 
int main()
{
    A a1(7);  // n=7
    A a2(a1); // 调用复制构造函数   a2.n=7
 
    B b;      // 调用 B 的隐式默认构造函数，进一步调用 A 的默认构造函数
    B b2 = b;
    A a3 = b; // 转换到 A& 并调用复制构造函数
 
    volatile A va(10);
    // A a4 = va; // 编译错误
 
    C c;
    // C c2 = c; // 编译错误,复制构造函数为 private
}