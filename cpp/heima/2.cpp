#include <iostream>


// �����ռ�����뷽ʽ   
//���������ռ�ĵ�һ�ַ�ʽ
//�ڶ���
using std::cout; //using �ؼ��� �����������������ռ� �������������ռ�һ������
using std::endl; 


//������
using namespace  std; //using namespace ���������������ռ�

int aa;//������Ĭ�ϵ�ȫ�������������ռ�


//��ζ���һ�������ռ�?
namespace namespaceA//����һ�������ռ� namespace�������ռ�ؼ������ͣ� namespaceA �������ռ������
{
	// namespace A �ռ�����
	int a = 10;

	int b = 20;
}

namespace namespaceB
{
	int a = 20;

	namespace namespaceC
	{
		struct teacher
		{
			int id;
			char name[64];
		};
	}

	namespace namespaceD
	{
		struct teacher
		{

		};
	}
}



//ʹ���Զ���������ռ�
void test()
{
	//using namespaceA::a;//���test�����������������е�a Ĭ�϶��� namespaceA�е�a
	//using namespace namespaceA; //��������namespaceA�ռ�
	cout << "A::a = " << namespaceA::a << endl;
	cout << "B::a = " << namespaceB::a << endl;
	//cout << "a = " << a << endl;


	//����һ��struct teacher�ı���
	//using namespace namespaceB::namespaceC;//��namepaceC�е����ж���ı���������
	//using namespaceB::namespaceC::teacher;

	//namespaceB::namespaceC::teacher t;
	using namespace namespaceB::namespaceC;
	teacher t;

}

int main(void)
{
	cout << "hello world" << endl;


	//��һ��ʹ�������ռ�����ķ�ʽ
	std::cout << "���" << std::endl;

	test();

	return 0;
}