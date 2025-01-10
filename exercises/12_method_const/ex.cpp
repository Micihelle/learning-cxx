#include <vector>
 
struct Array
{
    std::vector<int> data;
    Array(int sz) : data(sz) {} // 构造函数
 
    // const 成员函数；无法修改类的状态
    int operator[](int idx) const
    {                     // this 指针具有类型 const Array*
        return data[idx]; // 变换为 (*this).data[idx];
    }
 
    // 非 const 成员函数;可进行修改(左值)
    int& operator[](int idx)  
    {                     // this 指针具有类型 Array*
        return data[idx]; // 变换为 (*this).data[idx]
    }
};
 
int main()
{
    Array a(10);
    a[1] = 1;  // OK：a[1] 的类型是 int&
    const Array ca(10);
    ca[1] = 2; // 错误：ca[1] 的类型是 int
}