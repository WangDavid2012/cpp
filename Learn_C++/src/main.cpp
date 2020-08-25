#include <iostream>

using namespace std;

extern int string_test();
extern int string_test3();
extern int transform_test();
extern int operator_test();
extern int shareptr_test();

extern void linklist_test();
extern void HandleTest();

int main()
{
	cout << "C++ learn !" << endl;
	linklist_test();
	HandleTest();

	shareptr_test();
	operator_test();
	transform_test();
	string_test();
	string_test3();
	system("pause");
	return 0;
}
