#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


struct Teacher
{
	int id;
	char name[64];
};

int getTeacher(Teacher **pp)
{
	Teacher *p = NULL;

	p = (Teacher *)malloc(sizeof(Teacher));
	if (p == NULL)
	{
		cout << "error" << endl;
		return -1;
	}
	memset(p, 0, sizeof(Teacher));
	p->id = 30;
	strcpy(p->name, "zhang3");

	*pp = p;

	return 0;
}

int getTeacher02(Teacher* &tr) //tr 就是main中的tp 
{
	tr = (Teacher*)malloc(sizeof(Teacher));
	if (tr == NULL) {
		cout << "error" << endl;
		return -1;
	}

	tr->id = 40;
	strcpy(tr->name, "li4");

	return 0;
}

void freeTeacher02(Teacher * &tr)
{
	if (tr != NULL) {
		free(tr);
		tr = NULL;
	}
}

void freeTeacher(Teacher **pp)
{
	if (pp == NULL) {
		return;
	}
	Teacher *p = *pp;

	if (p != NULL) {
		free(p);
		*pp = NULL;
	}
}

int main(void)
{
	Teacher *tp = NULL;

	//getTeacher(&tp);
	getTeacher02(tp);

	cout << tp->id << ",  " << tp->name << endl;

	//freeTeacher(&tp);
	freeTeacher02(tp);

 
	
	return 0;
}