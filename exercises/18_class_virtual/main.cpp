#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const { // 没有用virtual修饰1意味着什么? 
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override {    // B::virtual_name()  override A::virtual_name()
        return 'B';
    }
    char direct_name() const {
        return 'B';  // 重新定义非虚函数
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    char virtual_name() const final {  //C.virtual_name()作为final(不会被派生类覆盖)
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};
struct D : public C {
    char direct_name() const {
        return 'D';
    }
};

int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    ASSERT(a.virtual_name() == 'A', MSG);
    ASSERT(b.virtual_name() == 'B', MSG); // B::virtual_name()覆盖基类A的A::virtual_name()
    ASSERT(c.virtual_name() == 'C', MSG);
    ASSERT(d.virtual_name() == 'C', MSG); // C::virtual_name()不会被派生类覆盖
    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG);

    A &rab = b; // 使用基类的指针或者引用来处理派生类：A的引用&rab指向b   通过引用来调用虚函数..（将基类引用A &rab绑定到了派生类对象b上）
    B &rbc = c;   
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG); //rab.virtual_name()调用的是 B::virtual_name() (在派生类B中覆盖了原先基类A中的A::virtual_name()
    ASSERT(rbc.virtual_name() == 'C', MSG);
    ASSERT(rcd.virtual_name() == 'C', MSG); // C::virtual_name()不会被派生类覆盖
    ASSERT(rab.direct_name() == 'A', MSG);  //why not B? 只有对virtual_name() 有override?
    ASSERT(rbc.direct_name() == 'B', MSG);  //why not C?
    ASSERT(rcd.direct_name() == 'C', MSG);  //why not D? 关键在于理解非虚函数和静态绑定

    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG); // rac.virtual_name()行为被 C::virtual_name()覆盖
    ASSERT(rbd.virtual_name() == 'C', MSG); // 为什么C::virtual_name()不会被派生类覆盖,编译器怎么知道自己需要作为D的父类/基类C的final字段？这是否属于C++本身的特性？
    ASSERT(rac.direct_name() == 'A', MSG);  // why not C? -> 非虚函数调用和静态绑定
    ASSERT(rbd.direct_name() == 'B', MSG);  // why not D? -> 非虚函数调用和静态绑定

    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG); // 多重继承，C::virtual_name()不会被派生类覆盖
    ASSERT(rad.direct_name() == 'A', MSG);  // why not D? 
                                            // A::direct_name()虽然没有virtual修饰，但是不是指向了派生类对象D吗？为什么不能调用D::direct_name()?

    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>
