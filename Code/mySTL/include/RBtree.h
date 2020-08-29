#ifndef _RBTREE_H_
#define _RBTREE_H_

#include "Utility.h"
#include "Construct.h"
#include "Iterator.h"
#include "Allocator.h"
#include "Algorithm.h"

namespace mySTL{
	typedef bool RBtree_color;
	const RBtree_color red = false;
	const RBtree_color black = true;

	struct RBtree_node_base
	{
		RBtree_color color;
		RBtree_node_base* parent;
		RBtree_node_base* left;
		RBtree_node_base* right;

		static RBtree_node_base* minimum(RBtree_node_base* x)
		{
			while(x->left!=nullptr)
				x = x->left;
			return x;
		}

		static RBtree_node_base* maximum(RBtree_node_base* x)
		{
			while(x->right!=nullptr)
				x = x->right;
			return x;
		}
	};

	template <class T>
	struct RBtree_node : public RBtree_node_base
	{
		typedef RBtree_node<T> Node;
		T data;
	};

	struct RBtree_iterator_base
	{
		typedef RBtree_node_base*	base_ptr;
		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t	difference_type;

		base_ptr node;

		void increment()
		{
			if (node->right != nullptr)
			{
				node = node->right;
				while(node->left != nullptr)
					node = node->left;
			}
			else
			{
				base_ptr y = node->parent;
				while(node == y->right)
				{
					node = y;
					y = y->parent;
				}
				if (node->right != y)
				{
					node = y;
				}
			}
		}

		void decrement()
		{
			if (node->color==red && node->parent->parent==node)
			{
				node = node->right;
			}
			else if (node->left!=nullptr)
			{
				base_ptr y = node->left;
				while(y->right != nullptr)
					y = y->right;
				node = y;
			}
			else
			{
				base_ptr y = node->parent;
				while(y->left == node)
				{
					node = y;
					y = y->parent;
				}	
				node = y;
			}
		}
	};

	template <class T,class Ref,class Ptr>
	struct RBtree_iterator :public RBtree_iterator_base
	{
		typedef T  		value_type;
		typedef Ref		reference;
		typedef Ptr 	pointer;
		typedef RBtree_iterator<T,T&,T*> 	iterator;
		typedef RBtree_iterator<T,const T&,const T*> const_iterator;
		typedef RBtree_node<T> Node;

		RBtree_iterator(){}
		RBtree_iterator(Node* x) {node = x;}         //子类指针赋给父类指针
		RBtree_iterator(const iterator& it) {node = it.node;}

		reference operator*() const {return ((Node*)node)->data;}
		pointer operator->() const {return &(operator*());}

		RBtree_iterator& operator++() {increment(); return *this;}
		RBtree_iterator operator++(int) 
		{
			RBtree_iterator temp = *this;
			increment();
			return temp;
		}
		RBtree_iterator& operator--() {decrement(); return *this;}
		RBtree_iterator operator--(int)
		{
			RBtree_iterator temp = *this;
			decrement();
			return temp;
		}

	};

	inline bool operator==(const RBtree_iterator_base& x,const RBtree_iterator_base& y)
	{
		return x.node == y.node;
	}

	inline bool operator!=(const RBtree_iterator_base& x,const RBtree_iterator_base& y)
	{
		return x.node != y.node;
	}

	inline void rotate_left(RBtree_node_base* x,RBtree_node_base*& root)
	{
		RBtree_node_base* y = x->right;
		x->right = y->left;
		if (y->left!=nullptr)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x==root)
		{
			root = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	inline void rotate_right(RBtree_node_base* x,RBtree_node_base*& root)
	{
		RBtree_node_base* y = x->left;
		x->left = y->right;
		if (y->right!=nullptr)
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x==root)
		{
			root = y;
		}
		else if (x==x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->right = x;
		x->parent = y;
	}

	//x为新插入点
	inline void rebalance(RBtree_node_base* x,RBtree_node_base*& root)
	{
		x->color = red;
		while(x!=root && x->parent->color==red)  //不为根节点&&父节点为红色（违反红黑树定义）
		{
			if(x->parent == x->parent->parent->left) //父为祖父的左子
			{
				RBtree_node_base* y = x->parent->parent->right;
				if (y && y->color==red)
				{
					x->parent->color = black;
					y->color = black;
					x->parent->parent->color = red;
					x = x->parent->parent;
				}
				else
				{
					if (x == x->parent->right)  //内，需预先旋转成外
					{
						x = x->parent;
						rotate_left(x,root);
					}
					x->parent->color = black;
					x->parent->parent->color = red;
					rotate_right(x->parent->parent,root);
				}
			}
			else
			{
				RBtree_node_base* y = x->parent->parent->left;
				if (y && y->color==red)
				{
					x->parent->color = black;
					y->color = black;
					x->parent->parent->color = red;
					x = x->parent->parent;
				}
				else
				{
					if (x == x->parent->left)
					{
						x = x->parent;
						rotate_right(x,root);
					}
					x->parent->color = black;
					x->parent->parent->color = red;
					rotate_left(x->parent->parent,root);
				}
			}
		}
		root->color = black;
	}

	//Z指向需要删除的节点，Y指向实质结构上被删除的
	inline RBtree_node_base* rebalance_for_erase(RBtree_node_base* z,RBtree_node_base*& root,
		RBtree_node_base*& leftmost,RBtree_node_base*& rightmost)
	{
	  	RBtree_node_base* y = z;
	  	RBtree_node_base* x = 0;
	  	RBtree_node_base* x_parent = 0;
	  	//y指向最终要删除的节点，x为y的子节点
	  	if (y->left == 0)     	// z 至多有一个非空子节点
	   		x = y->right;     
	  	else
	    	if (y->right == 0)  // z 只有一个左子节点
	      		x = y->left;    
		   	else 
		   	{              		// z 有两个非空子节点，y为z的后继
		      	y = y->right;  
		      	while (y->left != 0)
		        	y = y->left;
		      	x = y->right;
		    }
	  	if (y != z) 
	  	{   
	  		//swap(y,z)      
	    	z->left->parent = y; 		//1
	   	 	y->left = z->left;			//2
	    	if (y != z->right) 
	    	{
	    		//调节x_parent及x
	      		x_parent = y->parent;
	      		if (x) x->parent = y->parent;  
	      		y->parent->left = x; 

	      		y->right = z->right;	//3
	      		z->right->parent = y;	//4
	   	 	}
	   		else  //后继为右子节点
	      		x_parent = y;  
	    	if (root == z)              //5
	      		root = y;
	    	else if (z->parent->left == z)
	      		z->parent->left = y;
	    	else 
	      		z->parent->right = y;
	    	y->parent = z->parent;      //6
	    	mySTL::swap(y->color, z->color);
	    	y = z;
	    	// y现在指向最终要删除的节点
	  	}
	  	else 	// y == z
	  	{     
	  		//调整x及x_parent                   
	    	x_parent = y->parent;
	    	if (x) x->parent = y->parent;   
	    	if (root == z)
	      		root = x;
	    	else 
	      		if (z->parent->left == z)
	        		z->parent->left = x;
	      		else
	        		z->parent->right = x;
	        //更新最左节点	
	    	if (leftmost == z) 
	      		if (z->right == nullptr)       	 
	        		leftmost = z->parent;
	      		else
	        		leftmost = RBtree_node_base::minimum(x);
	        //更新最右节点
	    	if (rightmost == z)  
	      		if (z->left == 0)        		 
	        		rightmost = z->parent;  
	      		else                    
	        		rightmost = RBtree_node_base::maximum(x);
	  	}
	  	if (y->color != red) 	//删除黑色节点需要调整
	  	{ 
	    	while (x != root && (x == 0 || x->color == black))
	      		if (x == x_parent->left) 
	      		{
	        		RBtree_node_base* w = x_parent->right;//x的兄弟节点
	        		//case1:w为红色，则w的儿子必然全黑，w父亲x_parent也为黑
	        		//改变x_parent与w的颜色，同时对x_parent做一次左旋，这样就将情况1转变为情况2,3,4的一种
	        		if (w->color == red) 
	        		{
	          			w->color = black;
	          			x_parent->color = red;
	          			rotate_left(x_parent, root);
	          			w = x_parent->right;
	        		}
	        		//case2:w的双子均为黑，将w置黑
			        if ((w->left == 0 || w->left->color == black) && (w->right == 0 ||w->right->color == black)) 
			        {
			          	w->color = red;
			          	x = x_parent;
			          	x_parent = x_parent->parent;
			        } 
			        else 
			        {
			        	//case3:w左红右黑，交换w与左孩子的颜色，对w进行右旋，进行4
	          			if (w->right == 0 ||w->right->color == black) 
	          			{
	            			if (w->left) w->left->color = black;
					            w->color = red;
					        rotate_right(w, root);
					        w = x_parent->right;
	          			}
	          			//case4:右为红
	          			//交换w与父亲p颜色，同时对p做左旋。这样左边缺失的黑色就补回来了，同时，将w的右儿子置黑，这样左右都达到平衡
	          			w->color = x_parent->color;
	          			x_parent->color = black;
	          			if (w->right) w->right->color = black;
	          			rotate_left(x_parent, root);
	          			break;
	        		}
	      		} 
	      		else 
	      		{                  // same as above, with right <-> left.
		        	RBtree_node_base* w = x_parent->left;
		        	if (w->color == red) 
		        	{
		          		w->color = black;
		          		x_parent->color = red;
		          		rotate_right(x_parent, root);
		          		w = x_parent->left;
		        	}
		        	if ((w->right == 0 || w->right->color == black) &&(w->left == 0 || w->left->color == black)) 
		        	{
				          w->color = red;
				          x = x_parent;
				          x_parent = x_parent->parent;
		        	} 
		        	else 
		        	{
		          		if (w->left == 0 || w->left->color == black) 
		          		{
		            		if (w->right) w->right->color = black;
		            		w->color = red;
		            		rotate_left(w, root);
		            		w = x_parent->left;
		          		}
		          		w->color = x_parent->color;
						x_parent->color = black;
						if (w->left) w->left->color = black;
						rotate_right(x_parent, root);
						break;
		        	}
	    		}
		    //将x置黑
		    if (x) x->color = black;
	  	}
	  	return y;
	}


	template <class Key,class Value,class KeyOfValue,class Compare>
	class RBtree
	{
	public:
		typedef RBtree_node_base* base_ptr;
		typedef RBtree_node<Value> Node;
		typedef allocator<Node> nodeAllocator;

	public:
		typedef Key key_type;
		typedef Value value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef Node*	Link_type;

	protected:
		Node* create_node(const value_type& x)
		{
			Node* temp = nodeAllocator::allocate();
			construct(&temp->data,x);
			return temp;
		}
		void destroy_node(Node* p)
		{
			destroy(&p->data);
			nodeAllocator::deallocate(p);
		}
		Node* clone_node(Node* x)
		{
			Node *temp = nodeAllocator::allocate();
			temp->color = x->color;
			temp->left = x->left;
			temp->right = x->right;
			return temp;
		}

		Link_type& root() const { return (Link_type&) header->parent; }
	  	Link_type& leftmost() const { return (Link_type&) header->left; }
	  	Link_type& rightmost() const { return (Link_type&) header->right; }

	  	static Link_type& left(Link_type x){ return (Link_type&)(x->left); }
	  	static Link_type& right(Link_type x){ return (Link_type&)(x->right); }
	  	static Link_type& parent(Link_type x){ return (Link_type&)(x->parent); }
	  	static reference value(Link_type x){ return x->data; }
	  	static const Key& getKey(Link_type x){ return KeyOfValue()(value(x)); }
	  	static RBtree_color& color(Link_type x){ return (RBtree_color&)(x->color); }

	  	static Link_type& left(base_ptr x){ return (Link_type&)(x->left); }
	  	static Link_type& right(base_ptr x){ return (Link_type&)(x->right); }
	  	static Link_type& parent(base_ptr x){ return (Link_type&)(x->parent); }
	  	static reference value(base_ptr x){ return ((Link_type)x)->data; }
	  	static const Key& getKey(base_ptr x){ return KeyOfValue()(value(Link_type(x)));} 
	  	static RBtree_color& color(base_ptr x){ return (RBtree_color&)(Link_type(x)->color); }

	  	static Link_type minimum(Link_type x) { return (Link_type)  RBtree_node_base::minimum(x); }
	  	static Link_type maximum(Link_type x){ return (Link_type) RBtree_node_base::maximum(x); }

	public:
		typedef RBtree_iterator<value_type,reference,pointer> iterator;
		typedef RBtree_iterator<value_type,const_reference,const_pointer> const_iterator;
	protected:
		size_type node_count;
		Node* 	header;
		Compare key_compare;

	private:
		iterator insert(base_ptr pos,base_ptr par,const value_type& v);
		void erase_recursive(Node* x);
		Node* copy_tree(Node* x,Node* p);
		void clear(); 
		void init()
		{
			header = nodeAllocator::allocate();
			color(header) = red;
			root() = nullptr;
			leftmost() = header;
			rightmost() = header;
		}
	public:
		RBtree():node_count(0),header(nullptr),key_compare(){init();}
		RBtree(const Compare& comp):node_count(0),header(nullptr),key_compare(comp){init();}
		RBtree& operator=(const RBtree& x);
		~RBtree(){clear();destroy_node(header);}

		iterator begin() {return leftmost();}
		iterator end() {return header;}
		const_iterator begin()const {return leftmost();}
		const_iterator end()const {return header;}
		void swap(RBtree& t)
		{ 
			mySTL::swap(header,t.header); 
			mySTL::swap(node_count,t.node_count);
			mySTL::swap(key_compare,t.key_compare);
		}

		size_type size()const {return node_count;}
		bool empty()const {return node_count==0;}
		iterator find(const Key& k);
		const_iterator find(const Key& k)const;
		size_type count(const Key& k)const;
		//插入
		iterator insert_equal(const value_type& v);
		void insert_equal(const_iterator first,const_iterator last);
		void insert_equal(const value_type* first,const value_type* last);
		template <class InputIterator>
		void insert_equal(InputIterator first,InputIterator last);
		pair<iterator,bool> insert_unique(const value_type& v);
		void insert_unique(const_iterator first,const_iterator last);
		void insert_unique(const value_type* first,const value_type* last);
		template <class InputIterator>
		void insert_unique(InputIterator first,InputIterator last);

		//删除
		void erase(iterator position);
		size_type erase(const key_type& x);
		void erase(iterator first, iterator last);
		void erase(const Key* first,const Key* last);
		
		
		//边界
		iterator lower_bound(const Key& k);
		const_iterator lower_bound(const Key& k)const;
		iterator upper_bound(const Key& k);
		const_iterator upper_bound(const Key& k)const;
		pair<iterator,iterator> equal_range(const Key& key);
		pair<const_iterator,const_iterator> equal_range(const Key& key)const;
		
	};
}
#include "Detail/RBtree.impl.h"
#endif
