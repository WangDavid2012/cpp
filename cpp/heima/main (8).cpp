#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

#include "Employee.h"
#include "Technician.h"
#include "Manager.h"
#include "SaleMan.h"
#include "SalesManager.h"

using namespace std;

int main(void)
{


	Employee * person_array[] = { new Technician, new Manager, new SaleMan, new SalesManager };


	for (int i = 0; i < sizeof(person_array) / sizeof(person_array[0]); i++) {
		person_array[i]->init();
		person_array[i]->getPay();
		person_array[i]->uplevel(1);
		person_array[i]->displayStatus();
	}

	for (int i = 0; i < sizeof(person_array) / sizeof(person_array[0]); i++)
	{
		delete person_array[i];
	}


	return 0;
}