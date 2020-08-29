#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//ʹ���쳣�ķ�ʽ���д���


void my_strcpy1(char *dst, char *from) {
	if (dst == NULL) {
		throw 1; //1 ����Ŀ�ĵ�ַ������
	}
	else if (from == NULL) {
		throw 2; //2 ����Դ��ַ������
	}

	if (*from == 'a') {
		throw 3; //����copy���̳�������
	}


	while (*from != '\0') {
		*dst = *from;
		dst++;
		from++;
	}
	*dst = '\0';
}


void my_strcpy2(char* dst, char *from) 
{
	if (dst == NULL) {
		throw "Ŀ�ĵ�ַ������"; //1 ����Ŀ�ĵ�ַ������
	}
	else if (from == NULL) {
		throw "Դ��ַ������"; //2 ����Դ��ַ������
	}

	if (*from == 'a') {
		throw "copy���̳�������"; //����copy���̳�������
	}


	while (*from != '\0') {
		*dst = *from;
		dst++;
		from++;
	}
	*dst = '\0';
}

//Ŀ�ĵ�ַ��������쳣����
class BadDstAddrType{};
class BadSrcAddrType{};
class BadProcessAddrType{
public:
	BadProcessAddrType()
	{
		cout << "BadProcessAddrType().." << endl;
	}
	BadProcessAddrType(const BadProcessAddrType & obj)
	{
		cout << "BadProcessAddrType(const BadProcessAddrType &)..." << endl;
	}
	void print() {
		cout << "copy���̳������쳣" << endl;
	}
	~BadProcessAddrType(){
		cout << "~BadProcessAddrType()..." << endl;
	}
};

void my_strcpy3(char *dst, char *from)
{
	if (dst == NULL) {
		throw BadDstAddrType(); //1 ����Ŀ�ĵ�ַ������
	}
	else if (from == NULL) {
		throw BadSrcAddrType(); //2 ����Դ��ַ������
	}

	if (*from == 'a') {
		//throw new BadProcessAddrType(); //���׳����BadProcessAddrType() �ᴴ��һ���������� 
		throw BadProcessAddrType();
	}


	while (*from != '\0') {
		*dst = *from;
		dst++;
		from++;
	}
	*dst = '\0';
}

int main(void)
{
	char buf1[] = "a234567";
	char buf2[128] = { 0 };

	try {
		my_strcpy3(buf2, buf1);
	}
	catch (int e)
	{
		cout << "�����쳣����e = " << e << endl;
	}
	catch (char *e)
	{
		cout << "����char*�����쳣e = " << e << endl;
	}
	//catch (BadProcessAddrType e) { //BadProcessAddrType e = ��������temp //�ڲ����ʱ�������һ��Ԫ�ز���
													//�ᷢ���������죬�쳣����e�ͱ��׳���������������һ������
													//���������ǳ�����ķ���
//		cout << "������BadProcessAddrType �쳣����e  " << endl;
//		e.print();
//	}
	catch (BadProcessAddrType *e) { //��ʱ�Ǹ����������Ѿ����ͷ��ˣ�e��һ��Ұָ��
		cout << "������BadProcessAddrType* �쳣����e" << endl;
		delete e; //����׳����쳣������new�����ģ���Ҫ��ʾ��delete��
	}
	catch (BadProcessAddrType &e) { //1 ��ͨԪ�����͵��쳣���񣬲��ܹ��� ���ò���ͬʱ���ڡ�
		cout << "������ BadProcessAddrType & �쳣����" << endl;
		//����������ʹ�����ò���ģ���ô���������ͷŵ��������� �������쳣������֮�󣬲Ű�e�ͷš�
		//�������Ϊ BadProcessAddrType &e = BadProcessAddrType()
	}
	catch(...) 
	{
		cout << "����δ֪�쳣" << endl;
	}
}

#if 0
int my_strcpy(char *dst, char *from)
{
	if (dst == NULL) {
		return 1; //1 ����Ŀ�ĵ�ַ������
	}
	else if (from == NULL) {
		return 2; //2 ����Դ��ַ������
	}

	if (*from == 'a') {
		return 3; //����copy���̳�������
	}


	while (*from != '\0') {
		*dst = *from;
		dst++;
		from++;
	}
	*dst = '\0';

	return 0;
}

//��ͳ�Ĳ�����󷽷�
int main(void)
{
	char buf1[] = "a234567";
	char buf2[128] = { 0};
	int ret = 0;

	ret = my_strcpy(buf2, buf1);
	if (ret != 0) {
		switch (ret)
		{
		case 1:
			cout << "Ŀ�ĵ�ַ������" << endl;
			break;
		case 2:
			cout << "ԭ��ַ������" << endl;

			break;
		case 3:
			cout << "��������������" << endl;

			break;
		default:
			break;
		}
	}
	else {
		cout << "buf2 = " << buf2 << endl;
	}

	
	return 0;
}
#endif