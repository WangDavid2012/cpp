#include "MyArray.h"


MyArray::MyArray()
{
	this->space = NULL;
	this->length = 0;
}

MyArray::MyArray(int len)
{
	if (len <= 0) {
		this->length = 0;
		return;
	}
	else {
		this->length = len;
		this->space = new int[this->length]; //在堆上开辟了 长度为length的连续int空间
		cout << "数组的构造函数 MyArray::MyArray(int len) 被调用" << endl;
	}
}


//拷贝构造函数
MyArray::MyArray(const MyArray& another)
{
	if (another.length >= 0) {
		this->length = another.length;
		this->space = new int[this->length];

		for (int i = 0; i < this->length; i++) {
			this->space[i] = another.space[i];
		}

		cout << "拷贝构造函数 MyArray::MyArray(const MyArray& another) 被调用" << endl;
	}
}

MyArray & MyArray::operator=(const MyArray &another)
{
	if (this->space != NULL) {
		//之前有一定的堆内存空间需要释放
		delete [] this->space;
		this->space = 0;
		this->length = 0;
	}

	//进行拷贝 将another 给到自己，而是 深拷贝
	if (another.length > 0) {
		this->length = another.length;
		this->space = new int[this->length];//在堆上给space 开辟空间

		cout << " 重载了=号操作符" << endl;
		for (int i = 0; i < this->length; i++) {
			this->space[i] = another.space[i];
		}
	}

	return *this;
}


MyArray::~MyArray()
{
	if (this->space != NULL) {
		//此时space 有空间
		delete [] this->space;
		this->length = 0;
		this->space = NULL;
		cout << "MyArray::~MyArray() 被调用" << endl;
	}
}

int MyArray::getLen()
{
	return this->length;
}


//index 代表要赋值的数组的下标, data 数据
void MyArray::setData(int index, int data)
{
	if (this->space != NULL) {
		this->space[index] = data;
	}
}

int  MyArray::getData(int index)
{
	return this->space[index];
}


//实现操作符重载【】
int& MyArray::operator[](int index)  const //array[i]; array[i] = 10;  operator[](const Myarray * this, int index)
{
	return this->space[index];  //取值
}

//实现==操作符
bool MyArray::operator==(const MyArray & array)
{
	if (this->length != array.length) {
		return false;
	}
	else {
		for (int i = 0; i < this->length; i++) {
			if (this->space[i] != array.space[i]) {
				return false;
			}
		}
		return true;
	}
}

bool MyArray::operator!=(const MyArray &array)
{
	return !(*this == array);
}


//<<运算符重载
//operator<<(cout, array1);
ostream & operator<<(ostream &os,  const MyArray &array)
{
	os << "遍历了整个数组" << endl;
	for (int i = 0; i < array.length; i++) {
		os << array[i] << endl;
		//array.operator[](i);
		//array.operator[](&array, i)  // const MyArray *
	}

	return os;
}

istream & operator>>(istream &is, MyArray &array)
{
	cout << "请输入 " << array.length << "个数" << endl;
	for (int i = 0; i < array.length; i++) {
		is >> array[i];
	}

	return is;
}