#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;

#define SALE_DEPARTMENT  1 //销售部
#define DEVELOP_DEPARTMENT 2 //开发部
#define FINACIAL_DEPARTMENT 3 //财务部


class Yuangong{
public:
	string name;
	int age;
	string tele;
	double salary;

};

//创建员工 5名
void Create_Yuangong(vector<Yuangong>& v){

	string nameseed = "ABCDE";
	for (int i = 0; i < 5;i++){
		Yuangong yg;
		yg.name = "员工";
		yg.name += nameseed[i];

		yg.age = rand() % 30;
		yg.salary = rand() % 10000 + 10000;
		yg.tele = "+86-88888888";

		v.push_back(yg);
	}

}
//对员工指派部门
void Set_YG_Group(vector<Yuangong>& v, multimap<int, Yuangong>& group){
	
	for (vector<Yuangong>::iterator it = v.begin(); it != v.end(); it++){
		
		cout << "当前员工信息:" << endl;
		cout << "名字:" << it->name << " 年龄：" << it->age << " 工资:" << it->salary << " 电话" << it->tele << endl;
		int departmentID = -1;
		while (true){
			
			cout << "请输入部门(1 销售部 2 开发部 3 财务部) : " << endl;
			scanf("%d", &departmentID);

			if (departmentID == SALE_DEPARTMENT){
				group.insert(make_pair(SALE_DEPARTMENT,*it));
				break;
			}
			else if (departmentID == DEVELOP_DEPARTMENT){
				group.insert(make_pair(DEVELOP_DEPARTMENT, *it));
				break;
			}
			else if (departmentID == FINACIAL_DEPARTMENT){
				group.insert(make_pair(FINACIAL_DEPARTMENT, *it));
				break;
			}
			else{
				cout << "输入错误,请重新输入:" << endl;
			}
		}
	}
}


//打印各部门员工信息
void Show_YG_Info(multimap<int, Yuangong>& group){
	
	int departmentID = -1;
	while (true){

		cout << "请输入要查看的部门(1 销售部 2 开发部 3 财务部) : " << endl;
		scanf("%d", &departmentID);

		//验证输入有效性
		if (departmentID < 1 || departmentID > 3){
			continue;
		}

		multimap<int, Yuangong>::iterator pos = group.find(departmentID);
		int ygcount =  group.count(departmentID);
		int num = 0;
		while (pos != group.end() && num < ygcount){
			cout << "姓名: " << pos->second.name << " 年龄:" << pos->second.age <<  " 工资" << pos->second.salary << " 电话" << pos->second.tele <<  endl;
			num++;
			pos++;
		}
	
	}
}


int main(){

	//multimap 案例
	//公司今天招聘了 5 个员工，5 名员工进入公司之后，需要指派员工在那个部门工作
	//人员信息有: 姓名 年龄 电话 工资等组成
	//通过 Multimap 进行信息的插入 保存 显示
	//分部门显示员工信息 显示全部员工信息

	vector<Yuangong> v;  //放员工信息 未分组之前
	multimap<int, Yuangong> Ygroup;  //存放分组后的员工信息
	Create_Yuangong(v); //创建员工
	Set_YG_Group(v, Ygroup); //员工分组
	Show_YG_Info(Ygroup); //按分组显示员工信息

	system("pause");
	return EXIT_SUCCESS;
}
