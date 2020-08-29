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
		this->space = new int[this->length]; //�ڶ��Ͽ����� ����Ϊlength������int�ռ�
		cout << "����Ĺ��캯�� MyArray::MyArray(int len) ������" << endl;
	}
}


//�������캯��
MyArray::MyArray(const MyArray& another)
{
	if (another.length >= 0) {
		this->length = another.length;
		this->space = new int[this->length];

		for (int i = 0; i < this->length; i++) {
			this->space[i] = another.space[i];
		}

		cout << "�������캯�� MyArray::MyArray(const MyArray& another) ������" << endl;
	}
}


MyArray::~MyArray()
{
	if (this->space != NULL) {
		//��ʱspace �пռ�
		delete [] this->space;
		this->length = 0;
		this->space = NULL;
		cout << "MyArray::~MyArray() ������" << endl;
	}
}

int MyArray::getLen()
{
	return this->length;
}


//index ����Ҫ��ֵ��������±�, data ����
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
