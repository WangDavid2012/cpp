// C����

#if 0
#include <stdio.h>

int main(void)
{
	int a=  0;
	printf("hello world\n"); //�Ժ���Ļ���

	printf("������һ������");
	scanf("%d", &a);

	return 0;


}
#endif

#include <iostream>
//�����ռ��
using namespace std; //iostream ��һ�������ռ� ��std �� std{
	//																							cout
	//																					}
//  �����ʹ��cout endl �ȵ���Щ��׼��� һ��Ҫ���� std�����ռ�
// using namespace  std;


int main(void)
{
	int a = 0;

	cout << "hello world" <<endl; //cout ����һ����׼������� ���Ǻ���Ļ
													//endl ����C++�о���\n

	cout << "�����һ������" << endl;

	cin >> a;


	cout << "a = " << a << endl;

	return 0;
}