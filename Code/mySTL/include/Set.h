#ifndef _SET_H_
#define _SET_H_

#include "Utility.h"
#include "RBtree.h"
#include "Functional.h"
namespace mySTL 
{
	template <class Key,class Compare=less<Key>>
	class set
	{
	public:
	  	typedef Key     key_type;
	  	typedef Key     value_type;
	  	typedef Compare key_compare;
	  	typedef Compare value_compare;
	private:
	  	typedef RBtree<key_type, value_type,identity<value_type>, key_compare> RBtree_type;

	  	RBtree_type tree;  
	public:
	  	//typedef typename RBtree_type::const_pointer 		pointer;
	  	//typedef typename RBtree_type::const_pointer 		const_pointer;
	  	//typedef typename RBtree_type::const_reference 		reference;
	  	//typedef typename RBtree_type::const_reference 		const_reference;
	  	typedef typename RBtree_type::const_iterator 		iterator;
	  	//typedef typename RBtree_type::const_iterator 		const_iterator;
	  	typedef typename RBtree_type::size_type 			size_type;
	  	//typedef typename RBtree_type::difference_type 		difference_type;
	  	typedef typename RBtree_type::iterator 				tree_iterator;

	  	set(){}
	  	set(const set& x):tree(x.tree){}
	  	set& operator=(const set& s){tree = s.tree;return *this;}//重载赋值
	  	template <class InputIterator>
	  	set(InputIterator first,InputIterator last){ tree.insert_unique(first,last);}

	  	iterator begin()const {return tree.begin();}
	  	iterator end()const {return tree.end();}
	  	bool empty()const {return tree.empty();}
	  	size_type size()const {return tree.size();}
	  	void swap(set& x) {tree.swap(x.tree);}

	  	pair<iterator,bool> insert(const value_type& x)
	  	{
	  		pair<tree_iterator,bool> p = tree.insert_unique(x);
	  		return pair<iterator,bool>(p.first,p.second);
	  	}

	  	template<class InputIterator>
	  	void insert(InputIterator first,InputIterator last)
	  	{
	  		tree.insert_unique(first,last);
	  	}

	  	void erase(iterator position)
	  	{
	  		tree.erase((tree_iterator&)position);
	  	}

	  	size_type erase(const key_type& x)
	  	{
	  		return tree.erase(x);
	  	}

	  	void erase(iterator first,iterator last)
	  	{
	  		tree.erase((tree_iterator&)first,(tree_iterator&)last);
	  	}

	  	void clear() {tree.clear();}

	  	iterator find(const key_type& x) { return tree.find(x);}
	  	size_type count(const key_type& x) { return tree.count(x);}
	  	iterator lower_bound(const key_type& x) {return tree.lower_bound(x);}
	  	iterator upper_bound(const key_type& x) {return tree.upper_bound(x);}
	  	pair<iterator,iterator> equal_range(const key_type& x) {return tree.equal_range(x);}

	  	template <class K>
	  	friend bool operator== (const set<K>&,const set<K>&);
	  	template <class K>
	  	friend bool operator< (const set<K>&,const set<K>&);

	};


	template <class K>
	inline bool operator==( const set<K>& x,  const set<K>& y) 
	{
		return x.tree == y.tree;
	}

	template <class K>
	inline bool operator<( const set<K>& x,  const set<K>& y) 
	{
		return x.tree < y.tree;
	}

	template <class K>
	inline bool operator!=( const set<K>& x,  const set<K>& y) 
	{
		return !(x == y);
	}

	template <class K>
	inline bool operator>( const set<K>& x,  const set<K>& y) 
	{
		return y < x;
	}

	template <class K>
	inline bool operator<=( const set<K>& x,  const set<K>& y) 
	{
		return !(y < x);
	}

	template <class K>
	inline bool operator>=( const set<K>& x,  const set<K>& y) 
	{
		return !(x < y);
	}
}
#endif
