#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class eSize
{
public:
	eSize(int len)
	{
		this->len = len;
	}
	virtual void printErr() {
		cout << "eSize error: len = " << len << endl;
	}
protected:
	int len;
};

class eNagtive :public eSize
{
public:
	eNagtive(int len): eSize(len) {
	}

	virtual void printErr()
	{
		cout << "eNagtive error: len = " << len << endl;
	}
};

class eZero :public eSize
{
public:
	eZero(int len) :eSize(len) {

	}

	virtual void printErr()
	{
		cout << "eZero error: len = " << len << endl;
	}
};

class eTooBig :public eSize
{
public:
	eTooBig(int len) :eSize(len) {

	}

	virtual void printErr()
	{
		cout << "eTooBig error: len = " << len << endl;
	}
};

class eTooSmall :public eSize
{
public:
	eTooSmall(int len) :eSize(len) {

	}

	virtual void printErr()
	{
		cout << "eTooSmall error: len = " << len << endl;
	}
};

class MyArray
{
public:
	MyArray(int len)
	{
		if (len < 0) {
			throw eNagtive(len);
		}
		else if (len == 0) {
			throw eZero(len);
		}
		else if (len > 1000) {
			throw eTooBig(len);
		}
		else if (len < 10) {
			throw eTooSmall(len);
		}
		this->len = len;
		this->space = new int[len];
	}

	int & operator[](int index)
	{
		return this->space[index];
	}

	int getLen()
	{
		return this->len;
	}

	~MyArray() {
		if (this->space != NULL) {
			delete[] this->space;
			this->space = NULL;
			this->len = 0;
		}
	}
private:
	int len;//Ԫ�صĸ���
	int *space;
};

int main(void)
{
	try {
		MyArray array(3);

		for (int i = 0; i < array.getLen(); i++) {
			array[i] = i + 1;
		}

		for (int i = 0; i < array.getLen(); i++) {
			cout << array[i] << endl;
		}
	}
	catch (eSize &e) //eSize &e = eNagtive(len);
	{
		cout << "�����쳣" << endl;
		e.printErr();//������̬
	}

#if 0
	catch (eNagtive &e)
	{
		cout << "����eNagive �쳣" << endl;
		e.printErr();
	}
	catch (eZero &e) {
		cout << "����eZero �쳣" << endl;
		e.printErr();
	}
	catch (eTooBig &e) {
		cout << "����eTooBig �쳣" << endl;
		e.printErr();
	}
	catch (eTooSmall &e) {
		cout << "����eTooSmall �쳣" << endl;
		e.printErr();
	}
	catch (...)
	{
		cout << "����δ֪�쳣" << endl;
	}
#endif

	
	return 0;
}