#ifndef _RBTREE_IMPL_H
#define _RBTREE_IMPL_H
namespace mySTL{
	template <class Key,class Value,class KeyOfValue,class Compare>
	RBtree< Key, Value, KeyOfValue, Compare>& RBtree< Key, Value, KeyOfValue, Compare>::operator=
	(const RBtree< Key, Value, KeyOfValue, Compare>&x)
	{
		if (this!=&x)
		{
			clear();
			node_count = 0;
			key_compare = x.key_compare;
			if (x.root() == nullptr)
			{
				root() = nullptr;
				leftmost() = header;
				rightmost() = header;
			}
			else
			{
				root() = copy_tree(x.root(),header);
				leftmost() = minimum(root());
				rightmost() = maximum(root());
				node_count = x.node_count;
			}
		}
		return *this;
	}
	
	//pos为新值插入位置，parent为插入点父节点
	template <class Key,class Value,class KeyOfValue,class Compare>
	typename RBtree< Key, Value, KeyOfValue, Compare>::iterator
	RBtree< Key, Value, KeyOfValue, Compare>::insert(base_ptr pos,base_ptr par,const value_type& v)        
	{
		Node* x =(Node*)pos;
		Node* y = (Node*)par;
		Node* z;
		if (y==header || x!=nullptr || key_compare(KeyOfValue()(v),getKey(y)))
		{
			z = create_node(v);
			left(y) = z;
			if (y==header)
			{
				root() = z;
				rightmost() = z;
			}
			else if (y==leftmost())
			{
				leftmost() = z;
			}
		}
		else
		{
			z = create_node(v);
			right(y) = z;
			if (y==rightmost())
			{
				rightmost() = z;
			}
		}
		parent(z) = y;
		left(z) = nullptr;
		right(z) = nullptr;
		rebalance(z,header->parent);
		++node_count;
		return iterator(z);
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	typename RBtree< Key, Value, KeyOfValue, Compare>::iterator
	RBtree< Key, Value, KeyOfValue, Compare>::insert_equal(const value_type& v)   
	{
		Node* y = header;
		Node* x = root();
		while(x!=nullptr)
		{
			y = x;
			x = key_compare(KeyOfValue()(v),getKey(x))?left(x):right(x);
		}
		return insert(x,y,v);
	}     

	template <class Key,class Value,class KeyOfValue,class Compare>
	void RBtree< Key, Value, KeyOfValue, Compare>::insert_equal(const value_type* first,const value_type* last)  
	{
		while(first!=last)
		{
			insert_equal(*first);
			++first;
		}
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	void RBtree< Key, Value, KeyOfValue, Compare>::insert_equal(const_iterator first,const_iterator last)  
	{
		while(first!=last)
		{
			insert_equal(*first);
			++first;
		}
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	template <class InputIterator>
	void RBtree< Key, Value, KeyOfValue, Compare>::insert_equal(InputIterator first,InputIterator last)  
	{
		while(first!=last)
		{
			insert_equal(*first);
			++first;
		}
	}
	template <class Key,class Value,class KeyOfValue,class Compare>
	pair<typename RBtree<Key,Value, KeyOfValue, Compare>::iterator,bool>
	RBtree< Key, Value, KeyOfValue, Compare>::insert_unique(const value_type& v)  
	{
		Node* y = header;
		Node* x = root();
		bool isLeft = true;
		while(x!=0)
		{
			y = x;
			isLeft = key_compare(KeyOfValue()(v),getKey(x));
			x = isLeft?left(x):right(x);
		}

		iterator j = iterator(y);
		if (isLeft)
		{
			if (j==begin())
			{
				return pair<iterator,bool>(insert(x,y,v),true);
			}
			else
			{
				--j;
			}
		}
		if (key_compare(getKey(j.node),KeyOfValue()(v)))
		{
			return pair<iterator,bool>(insert(x,y,v),true);
		}
		return pair<iterator,bool>(j,false);
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	void RBtree< Key, Value, KeyOfValue, Compare>::insert_unique(const value_type* first,const value_type* last)  
	{
		while(first!=last)
		{
			insert_unique(*first);
			++first;
		}
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	void RBtree< Key, Value, KeyOfValue, Compare>::insert_unique(const_iterator first,const_iterator last)  
	{
		while(first!=last)
		{
			insert_unique(*first);
			++first;
		}
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	template <class InputIterator>
	void RBtree< Key, Value, KeyOfValue, Compare>::insert_unique(InputIterator first,InputIterator last)  
	{
		while(first!=last)
		{
			insert_unique(*first);
			++first;
		}
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	typename RBtree< Key, Value, KeyOfValue, Compare>::iterator
	RBtree< Key, Value, KeyOfValue, Compare>::find(const Key& k)
	{
		Node* y = header;
		Node* x = root();
		while(x!=nullptr)
		{
			if (!key_compare(getKey(x),k))
			{	
				y = x,x = left(x);
			}
			else
			{
				x = right(x);
			}
		}
		iterator j = iterator(y);
		return (j==end() || key_compare(k,getKey(j.node)))?end():j;
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	typename RBtree< Key, Value, KeyOfValue, Compare>::const_iterator
	RBtree< Key, Value, KeyOfValue, Compare>::find(const Key& k)const
	{
		Node* y = header;
		Node* x = root();
		while(x!=nullptr)
		{
			if (!key_compare(getKey(x),k))
			{	
				y = x,x = left(x);
			}
			else
			{
				x = right(x);
			}
		}
		iterator j = iterator(y);
		return (j==end() || key_compare(k,getKey(j.node)))?end():j;
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	typename RBtree< Key, Value, KeyOfValue, Compare>::size_type
	RBtree< Key, Value, KeyOfValue, Compare>::count(const Key& k)const
	{
		pair<const_iterator,const_iterator> p = equal_range(k);
		return distance(p.first,p.second);
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	void RBtree< Key, Value, KeyOfValue, Compare>::erase(iterator position)
	{
		Node* y = (Node*)rebalance_for_erase(position.node,header->parent,header->left,header->right);
		destroy_node(y);
		--node_count;
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	typename RBtree< Key, Value, KeyOfValue, Compare>::size_type
	RBtree< Key, Value, KeyOfValue, Compare>::erase(const Key& x)
	{
		pair<iterator,iterator> p = equal_range(x);
		size_type n = distance(p.first,p.second);
		erase(p.first,p.second);
		return n;
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	void RBtree< Key, Value, KeyOfValue, Compare>::erase_recursive(Node* x)
	{
		while(x!=nullptr)
		{
			erase_recursive(right(x));
			Node* y = left(x);
			destroy_node(x);
			x = y;
		}
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	void RBtree< Key, Value, KeyOfValue, Compare>::erase(iterator first,iterator last)
	{
		if (first==begin()&&last==end())
		{
			clear();
		}
		else
		{
			while(first!=last)
				erase(first++);
		}
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	void RBtree< Key, Value, KeyOfValue, Compare>::erase(const Key* first,const Key* last)
	{
		while(first!=last)
			erase(*first++);
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	typename RBtree< Key, Value, KeyOfValue, Compare>::Node* 
	RBtree< Key, Value, KeyOfValue, Compare>::copy_tree(Node* x,Node* p)
	{
		Node* root = clone_node(x);
		root->parent = p;

		if (x->right)
		{
			root->right = copy_tree(right(x),root);
		}
		p = root;
		x = left(x);

		while(x!=nullptr)
		{
			Node* y = clone_node(x);
			p->left = y;
			y->parent = p;
			if (x->right)
			{
				y->right = copy_tree(right(x),y);
			}
			p = y;
			x = left(x);
		}
		return root;
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	void RBtree< Key, Value, KeyOfValue, Compare>::clear()
	{
		if (node_count!=0)
		{
			erase_recursive(root());
			leftmost() = header;
			root() = nullptr;
			rightmost() = header;
			node_count = 0;
		}
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	typename RBtree< Key, Value, KeyOfValue, Compare>::iterator
	RBtree< Key, Value, KeyOfValue, Compare>::lower_bound(const Key& k)
	{
		Node* y = header;
		Node* x = root();
		while(x!=nullptr)
		{
			if (!key_compare(getKey(x),k)) //x>=k
			{
				y = x;
				x = left(x);
			}
			else
			{
				x = right(x);
			}
		}
		return iterator(y);
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	typename RBtree< Key, Value, KeyOfValue, Compare>::const_iterator
	RBtree< Key, Value, KeyOfValue, Compare>::lower_bound(const Key& k)const
	{
		Node* y = header;
		Node* x = root();
		while(x!=nullptr)
		{
			if (!key_compare(getKey(x),k)) //x>=k
			{
				y = x;
				x = left(x);
			}
			else
			{
				x = right(x);
			}
		}
		return const_iterator(y);
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	typename RBtree< Key, Value, KeyOfValue, Compare>::const_iterator
	RBtree< Key, Value, KeyOfValue, Compare>::upper_bound(const Key& k)const
	{
		Node* y = header;
		Node* x = root();
		while(x!=nullptr)
		{
			if (key_compare(k,getKey(x))) //x>k,相同的是放在左边的
			{
				y = x;
				x = left(x);
			}
			else
			{
				x = right(x);
			}
		}
		return const_iterator(y);
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	typename RBtree< Key, Value, KeyOfValue, Compare>::iterator
	RBtree< Key, Value, KeyOfValue, Compare>::upper_bound(const Key& k)
	{
		Node* y = header;
		Node* x = root();
		while(x!=nullptr)
		{
			if (key_compare(k,getKey(x))) //k>x
			{
				y = x;
				x = left(x);
			}
			else
			{
				x = right(x);
			}
		}
		return iterator(y);
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	inline pair<typename RBtree< Key, Value, KeyOfValue, Compare>::iterator,
				typename RBtree< Key, Value, KeyOfValue, Compare>::iterator>
	RBtree< Key, Value, KeyOfValue, Compare>::equal_range(const Key& key)
	{
		return pair<iterator,iterator>(lower_bound(key),upper_bound(key));
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	inline pair<typename RBtree< Key, Value, KeyOfValue, Compare>::const_iterator,
				typename RBtree< Key, Value, KeyOfValue, Compare>::const_iterator>
	RBtree< Key, Value, KeyOfValue, Compare>::equal_range(const Key& key)const
	{
		return pair<const_iterator,const_iterator>(lower_bound(key),upper_bound(key));
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	inline bool 
	operator==(const RBtree< Key, Value, KeyOfValue, Compare>& x, 
	           const RBtree< Key, Value, KeyOfValue, Compare>& y)
	{
	  return x.size() == y.size() && equal(x.begin(), x.end(), y.begin());
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	inline bool 
	operator<(const RBtree< Key, Value, KeyOfValue, Compare>& x, 
	          const RBtree< Key, Value, KeyOfValue, Compare>& y)
	{
	  return lexicographical_compare(x.begin(), x.end(), 
	                                 y.begin(), y.end());
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	inline bool 
	operator!=(const RBtree< Key, Value, KeyOfValue, Compare>& x, 
	           const RBtree< Key, Value, KeyOfValue, Compare>& y) {
	  return !(x == y);
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	inline bool 
	operator>(const RBtree< Key, Value, KeyOfValue, Compare>& x, 
	          const RBtree< Key, Value, KeyOfValue, Compare>& y) {
	  return y < x;
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	inline bool 
	operator<=(const RBtree< Key, Value, KeyOfValue, Compare>& x, 
	           const RBtree< Key, Value, KeyOfValue, Compare>& y) {
	  return !(y < x);
	}

	template <class Key,class Value,class KeyOfValue,class Compare>
	inline bool 
	operator>=(const RBtree< Key, Value, KeyOfValue, Compare>& x, 
	           const RBtree< Key, Value, KeyOfValue, Compare>& y) {
	  return !(x < y);
	}
}
#endif
