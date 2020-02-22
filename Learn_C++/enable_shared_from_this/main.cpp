#include <memory>
#include <iostream>

class Bad
{
public:
	std::shared_ptr<Bad> getptr() {
		return std::shared_ptr<Bad>(this);
	}
	~Bad() { std::cout << "Bad::~Bad() called" << std::endl; }
};

int main()
{
	// �����ʾ����ÿ��shared_ptr����Ϊ�Լ��Ƕ�����е�������
	std::shared_ptr<Bad> bp1(new Bad());
	std::shared_ptr<Bad> bp2 = bp1->getptr();
	// ��ӡbp1��bp2�����ü���
	std::cout << "bp1.use_count() = " << bp1.use_count() << std::endl;
	std::cout << "bp2.use_count() = " << bp2.use_count() << std::endl;
}  // Bad ���󽫻ᱻɾ������