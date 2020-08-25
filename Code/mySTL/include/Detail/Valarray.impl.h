##ifndef _VALARRAY_IMPL_H
#define _VALARRAY_IMPL_H
namespace mySTL{
	//***********************构造，复制，析构相关***********************
	template <class T,class Alloc = allocator<T>>
	valarray<T,Alloc>::valarray():size(0),data(0){}

	template <class T,class Alloc = allocator<T>>
	valarray<T,Alloc>::valarray(size_t n):data(0){size = n;}

	template <class T,class Alloc = allocator<T>>
	valarray<T,Alloc>::valarray(const T& val, size_t n){
		size = n;
		mySTL::uninitialized_fill_n(data, n, val);
	}

	template <class T,class Alloc = allocator<T>>
	valarray<T,Alloc>::valarray(const T* val, size_t n){
		size = n;
		mySTL::uninitialized_fill_n(data, n, val);
	}

	template <class T,class Alloc = allocator<T>>
	valarray<T,Alloc>::valarray(const valarray& x){
		mySTL::uninitialized_copy(x.data, x.size,
                       this->data);
	}

	template <class T,class Alloc = allocator<T>>
	valarray<T,Alloc>::~valarray(){
		destroy(data);
	}

	template <class T,class Alloc = allocator<T>>
	valarray<T,Alloc>::size_t size() const{
		return size;
	}

	template <class T,class Alloc = allocator<T>>
	valarray<T,Alloc>::T sum() const{
		T sum;
		while(n){

		}
	}
} 
#endif