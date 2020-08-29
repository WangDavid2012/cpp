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

MyArray & MyArray::operator=(const MyArray &another)
{
	if (this->space != NULL) {
		//֮ǰ��һ���Ķ��ڴ�ռ���Ҫ�ͷ�
		delete [] this->space;
		this->space = 0;
		this->length = 0;
	}

	//���п��� ��another �����Լ������� ���
	if (another.length > 0) {
		this->length = another.length;
		this->space = new int[this->length];//�ڶ��ϸ�space ���ٿռ�

		cout << " ������=�Ų�����" << endl;
		for (int i = 0; i < this->length; i++) {
			this->space[i] = another.space[i];
		}
	}

	return *this;
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


//ʵ�ֲ��������ء���
int& MyArray::operator[](int index)  const //array[i]; array[i] = 10;  operator[](const Myarray * this, int index)
{
	return this->space[index];  //ȡֵ
}

//ʵ��==������
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


//<<���������
//operator<<(cout, array1);
ostream & operator<<(ostream &os,  const MyArray &array)
{
	os << "��������������" << endl;
	for (int i = 0; i < array.length; i++) {
		os << array[i] << endl;
		//array.operator[](i);
		//array.operator[](&array, i)  // const MyArray *
	}

	return os;
}

istream & operator>>(istream &is, MyArray &array)
{
	cout << "������ " << array.length << "����" << endl;
	for (int i = 0; i < array.length; i++) {
		is >> array[i];
	}

	return is;
}