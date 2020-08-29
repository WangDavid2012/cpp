#ifndef _STACK_H_
#define _STACK_H_

#include "Vector.h"

namespace mySTL{
	//class of stack
	template<class T, class Container = mySTL::vector<T>>
	class stack{
	public:
		typedef typename Container::value_type value_type;
		typedef typename Container::reference reference;
		typedef typename Container::size_type size_type;
		typedef Container container_type;
	private:
		container_type container_;
	public:
		explicit stack(const container_type& ctnr = container_type()) :container_(ctnr){}

		bool empty() const{ return container_.empty(); }
		size_type size() const{ return container_.size(); }
		value_type& top(){ return (container_.back()); }
		const value_type& top() const{ return (container_.back()); }
		void push(const value_type& val){ container_.push_back(val); }
		void pop(){ container_.pop_back(); }
		void swap(stack& x){ mySTL::swap(container_, x.container_); }
	public:
		template <class ELEM, class container>
		friend bool operator== (const stack<ELEM, container>& lhs, const stack<ELEM, container>& rhs);
		template <class ELEM, class container>
		friend bool operator!= (const stack<ELEM, container>& lhs, const stack<ELEM, container>& rhs);
		
		template <class ELEM, class container>
		friend void swap(stack<ELEM, container>& x, stack<ELEM, container>& y);
	};
	template <class T, class Container>
	bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs){
		return lhs.container_ == rhs.container_;
	}
	template <class T, class Container>
	bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs){
		return lhs.container_ != rhs.container_;
	}
	template <class T, class Container>
	void swap(stack<T, Container>& x, stack<T, Container>& y){
		x.swap(y);
	}
	
}
#endif