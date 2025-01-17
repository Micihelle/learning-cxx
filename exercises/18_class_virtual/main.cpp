#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override {    //B::virtual_name()覆盖A::virtual_name()
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    char virtual_name() const final {  //virtual_name()不会被派生类覆盖
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

    A &rab = b; // 通过引用来调用虚函数..（将基类引用A &rab绑定到了派生类对象b上）
    B &rbc = c;   
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG); //B::virtual_name()覆盖A::virtual_name()
    ASSERT(rbc.virtual_name() == 'C', MSG);
    ASSERT(rcd.virtual_name() == 'C', MSG); // C::virtual_name()不会被派生类覆盖
    ASSERT(rab.direct_name() == 'A', MSG);  //why not B? 只有对virtual_name() 有override?
    ASSERT(rbc.direct_name() == 'B', MSG);  //why not C?
    ASSERT(rcd.direct_name() == 'C', MSG);  //why not D?

    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG);
    ASSERT(rbd.virtual_name() == 'C', MSG); // C::virtual_name()不会被派生类覆盖
    ASSERT(rac.direct_name() == 'A', MSG);  // why not C?
    ASSERT(rbd.direct_name() == 'B', MSG);  // why not D?

    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG); // 多重继承，C::virtual_name()不会被派生类覆盖
    ASSERT(rad.direct_name() == 'A', MSG);  // why not D? 
                                            // A::direct_name()虽然没有virtual修饰，但是不是指向了派生类对象D吗？为什么不能调用D::direct_name()?

    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>
