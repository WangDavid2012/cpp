#include <iostream>
#include <string>
#include <vector>
#include "node.h"

using namespace std;
using std::vector;



extern void deleteNode(ListNode *node);
extern int treetest1();


int main()
{
	struct ListNode n1 = {5,nullptr};
	deleteNode(&n1);

	int value = treetest1();

	cout << "the value is " << value << endl;

	system("pause");

}