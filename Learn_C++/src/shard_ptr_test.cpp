//�μ���ַ��https://blog.csdn.net/caoshangpa/article/details/79392878
#include <memory>
#include <iostream>

/****************************************************************************************
C++ ��׼���������ģ��:enable_shared_from_this
enable_shared_from_this����һ����ָ��weak_ptr,�����ָ���ܹ�����this
�ڵ���enabled_shard_form_this()�������ʱ����������ڲ�ʵ�ʵ��������weak_ptr��lock����
lock()��������shard_ptrָ�������1��ͬʱ����shard_ptr,����ǹ���ԭ��

***************************************************************************************/


class Bad
{
public:
	std::shared_ptr<Bad> getptr() {
		return std::shared_ptr<Bad>(this);
	}
	~Bad() {
		std::cout << "Bad::~Bad() called" << std::endl;
	}
};

void test1()
{
	// �����ʾ����ÿ��shared_ptr����Ϊ�Լ��Ƕ�����е�������
	std::shared_ptr<Bad> bp1(new Bad());
	std::shared_ptr<Bad> bp2 = bp1->getptr();
	// ��ӡbp1��bp2�����ü���
	std::cout << "bp1.use_count() = " << bp1.use_count() << std::endl;
	std::cout << "bp2.use_count() = " << bp2.use_count() << std::endl;
}  // Bad ���󽫻ᱻɾ������


   //��ȷ��ʵ��
struct Good : std::enable_shared_from_this<Good> // ע�⣺�̳�
{
public:
	std::shared_ptr<Good> getptr() {
		return shared_from_this();
	}
	~Good() {
		std::cout << "Good::~Good() called" << std::endl;
	}
};


void test2()
{
	// ����������������������������ָ�������system("pause")֮ǰ����
	{
		std::shared_ptr<Good> gp1(new Good());
		std::shared_ptr<Good> gp2 = gp1->getptr();
		// ��ӡgp1��gp2�����ü���
		std::cout << "gp1.use_count() = " << gp1.use_count() << std::endl;
		std::cout << "gp2.use_count() = " << gp2.use_count() << std::endl;
	}
	system("pause");
}






int shared_ptr_test0()
{
	test1();
	test2();
	return 0;
}