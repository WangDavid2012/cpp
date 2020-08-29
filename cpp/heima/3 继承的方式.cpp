#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//基类
class Parent
{
public: //访问控制权限
	int pub; //对内部外部均可以
protected:
	int pro;//对内，外均不可以  //protected 访问控制权限下的成员 儿子可见
private:
	int pri;//对内外 均不可以  //父亲的情人  //private 访问控制权限下的成员 儿子不可见
};

class Child :public Parent //Child 公有继承 Parent
{
	void func()
	{
		pro; //ok//可能是私有的和保护的。
		//pri; //访问不了父亲的私有成员
	}
};

//三看原则:
//1  看当前的成员调用是在类的外部 还是在类的内部
//2 看儿子的继承方式， 是公有继承还是 私有继承
//3 看当前的成员变量在父亲中的访问控制权限

class Child2 : protected Parent
{
	void func()
	{
		pub; //内部  //此时pub 函数 在此类中是 protected权限
		//pri;
	}
};

class Child3 : private Parent
{
	void func()
	{
		pub; //父亲中的public 变成 本来的私有
		pro;//父亲中的pro  变成本类的私有
	}
};

class SubChild3 : public Child3
{

	void func()
	{
		pub;
		pro;
	}
};

//1 基类中的私有成员 不管子类如何继承， 子类都访问不了。
//2 如果是公有(public)继承， 那么基类中的访问控制权限 出了私有成员 ，在子类中保持不变
//3 如果是保护继承protected ， 那么子类中出了基类的私有成员，全部是protected权限
//4 如果是私有继承 private  ， 父类中除了私有成员， 在子类都是 私有成员。

int main(void)
{
	Parent p;
	p.pub;

	Child c;
	c.pub; // 
	Child c;
//	c.pro; //
	//c.pro; //此时pro 可能是私有的 也可能是保护的。

	Child2 c2;
	//c2.pub;
	//c2.pro; //此时pro 在Child2中是一个保护权限， 在类的外部访问不了。
	Child3 c3;
	c3.pub;
	c3.pro;

	return 0;
}