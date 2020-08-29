#ifndef _MULTIMAP_H_
#define _MULTIMAP_H_

#include "Utility.h"
#include "RBtree.h"
#include "Functional.h"

namespace mySTL
{
    template <class Key,class T,class Compare=less<Key>>
	class multimap	
	{
	public:
	    typedef Key                  key_type;
	    typedef T                    data_type;
	    typedef T                    multimapped_type;
	    typedef pair<const Key, T>   value_type;
	    typedef Compare              key_compare;

	private:
	    typedef RBtree<key_type, value_type, select1st<value_type>, key_compare> RBtree_type;
	    RBtree_type tree;

	public:
	    typedef typename RBtree_type::pointer pointer;
	    typedef typename RBtree_type::const_pointer const_pointer;
	    typedef typename RBtree_type::reference reference;
	    typedef typename RBtree_type::const_reference const_reference;
	    typedef typename RBtree_type::iterator iterator;
	    typedef typename RBtree_type::const_iterator const_iterator;
	    typedef typename RBtree_type::size_type size_type;
	    typedef typename RBtree_type::difference_type difference_type;

	 	multimap(){}
	  	multimap(const multimap& x):tree(x.tree){}
	  	multimap& operator=(const multimap& m){tree = m.tree;return *this;}
	  	template <class InputIterator>
	  	multimap(InputIterator first,InputIterator last){ tree.insert_equal(first,last);}

		iterator begin() {return tree.begin();}
		iterator end() {return tree.end();}
		const_iterator begin()const {return tree.begin();}
		const_iterator end()const {return tree.end();}

		bool empty()const {return tree.empty();}
		size_type size()const {return tree.size();}

		void swap(multimap& x) {tree.swap(x.tree);}

		//插入删除
		iterator insert(const value_type& x)
		{
			return tree.insert_equal(x);
		}

		template<class InputIterator>
	  	void insert(InputIterator first,InputIterator last)
	  	{
	  		tree.insert_equal(first,last);
	  	}

	  	void erase(iterator position)
	  	{
	  		tree.erase(position);
	  	}

	  	size_type erase(const key_type& x)
	  	{
	  		return tree.erase(x);
	  	}

	  	void erase(iterator first,iterator last)
	  	{
	  		tree.erase(first,last);
	  	}

	  	void clear() {tree.clear();}

	  	iterator find(const key_type& x) {return tree.find(x);}
	  	iterator find(const key_type& x)const { return tree.find(x);}
	  	size_type count(const key_type& x)const { return tree.count(x);}

	  	iterator lower_bound(const key_type& x) {return tree.lower_bound(x);}
	  	iterator upper_bound(const key_type& x) {return tree.upper_bound(x);}
	  	const_iterator lower_bound(const key_type& x)const {return tree.lower_bound(x);}
	  	const_iterator upper_bound(const key_type& x)const {return tree.upper_bound(x);}
	  	pair<iterator,iterator> equal_range(const key_type& x) {return tree.equal_range(x);}
	  	pair<const_iterator,const_iterator> equal_range(const key_type& x)const {return tree.equal_range(x);}

	  	template <class K,class ELEM>
	  	friend bool operator== (const multimap<K,ELEM>&,const multimap<K,ELEM>&);
	  	template <class K,class ELEM>
	  	friend bool operator< (const multimap<K,ELEM>&,const multimap<K,ELEM>&);
	};

	template <class K,class T>
	inline bool operator==( const multimap<K,T>& x,  const multimap<K,T>& y) 
	{
		return x.tree == y.tree;
	}

	template <class K,class T>
	inline bool operator<( const multimap<K,T>& x,  const multimap<K,T>& y) 
	{
		return x.tree < y.tree;
	}

	template <class K,class T>
	inline bool operator!=( const multimap<K,T>& x,  const multimap<K,T>& y) 
	{
		return !(x == y);
	}

	template <class K,class T>
	inline bool operator>( const multimap<K,T>& x,  const multimap<K,T>& y) 
	{
		return y < x;
	}

	template <class K,class T>
	inline bool operator<=( const multimap<K,T>& x,  const multimap<K,T>& y) 
	{
		return !(y < x);
	}

	template <class K,class T>
	inline bool operator>=( const multimap<K,T>& x,  const multimap<K,T>& y) 
	{
		return !(x < y);
	}
}
#endif
