#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>

using namespace std;

void test_write_to_file()
{
	//需要创建一个文件的输出流cout ostream,  fout ofstream
	char *file_name = "c:/test/hahaha.txt";

	ofstream fout(file_name, ios::app | ios::out); //如果不写这个打开文件的控制符，默认是ios::out
	if (!fout) {
		cout << "打开文件失败" << endl;
	}

	fout << "hello...111" << endl;
	fout << "hello...2 "22" << endl;
		fout << hello...333" << endl;


	fout.close();
}

void test_read_from_file()
{
	char *file_name = "c:/test/hahaha.txt";

	ifstream fin(file_name, ios::in); //ios::in
	if (!fin) {
		cout << "打开文件失败" << endl;
	}
	char ch;
	while (fin.get(ch)) {
		cout << ch;
	}

	fin.close();
}


class Teacher
{
public:
	Teacher() {

	}
	Teacher(int id, char *name)
	{
		this->id = id;
		strcpy(this->name, name);
	}
	void printT() {
		cout << "id = " << id << endl;
		cout << "name = " << name << endl;
	}
private:
	int id;
	char name[32];
};

void test_write_binary_to_file()
{
	char *file_name = "c:/test/bin_teacher.dat";
	Teacher t1(1, "zhang3");
	Teacher t2(2, "li4");

	ofstream fout(file_name, ios::binary);
	if (!fout) {
		cout << "打开文件失败" << endl;
		return;
	}

	fout.write((char*)&t1, sizeof(Teacher));
	fout.write((char*)&t2, sizeof(Teacher));

	fout.close();
}

void test_read_binary_from_file()
{
	char *file_name = "c:/test/bin_teacher.dat";
	Teacher temp1;
	Teacher temp2;


	ifstream fin(file_name, ios::binary);
	if (!fin) {
		cout << "打开文件失败" << endl;
		return;
	}

	fin.read((char*)&temp1, sizeof(Teacher));
	temp1.printT();
	fin.read((char*)&temp2, sizeof(Teacher));
	temp2.printT();

	fin.close();
}

int main(void)
{
	//test_write_to_file();
	//test_read_from_file();
	//test_write_binary_to_file();
	test_read_binary_from_file();
	return 0;
}