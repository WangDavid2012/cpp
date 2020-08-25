#ifndef _VALARRAY_H_
#define _VALARRAY_H_

#include "Iterator.h"
#include "ReverseIterator.h"
#include "Algorithm.h"
#include "Allocator.h"

namespace mySTL{
template <class T,class Alloc = allocator<T>>
class valarray
{ 
public: 
    typedef T value_type;

    // 构造和析构
    valarray(); 
    explicit valarray(size_t);
    valarray(const T&, size_t);
    valarray(const T*, size_t);
    valarray(const valarray&);
    ~valarray();

    // member functions
    size_t size() const;
    T    sum() const;
    T    min() const;
    T    max() const;
    void resize(size_t size, T c = T());

    // 移位, 正数左移, 负数右移
    valarray<T> shift (int) const;
    valarray<T> cshift(int) const; // 循环移位

    // 对所有元素执行func函数
    valarray<T> apply (T func(T)) const;
    valarray<T> apply (T func(const T&)) const;

private:
    size_t size;
    T* data;
};
}
#include "Detail/Valarray.impl.h"
#endif

