/********************************************************************
文件说明：
	主要用总结数据结构，测试写的代码是否可以正常运行
	实现的功能如下：
	测试循环队列    
	测试堆的操作
	测试栈的操作
	测试单向链表
	测试双向链表
	测试二叉树
	霍夫曼树测试
	测试二叉树前序，中序，后序遍历
*********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "heap.h"
#include "singlelinkedlist.h"
#include "bz_stack.h"
#include "my_tree.h"
#include "search.h"
#include "tlist.h"


int main()
{
	//这几个算法，均经过了验证

	ParentNodeAddr_Test();
	QueueFunction_Test();   //测试循环队列
	StackTest();             //测试栈操作
	SearchTest();           //排序算法测试
	bz_stackTest();         //栈操作测试



	//关于树的操作函数有问题，不做测试了  david  2018-10-09
	//MyTreeTest();
	//my_tree_test();
	getchar();

	return 0;
}