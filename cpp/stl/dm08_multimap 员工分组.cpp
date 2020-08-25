#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;

#define SALE_DEPARTMENT  1 //���۲�
#define DEVELOP_DEPARTMENT 2 //������
#define FINACIAL_DEPARTMENT 3 //����


class Yuangong{
public:
	string name;
	int age;
	string tele;
	double salary;

};

//����Ա�� 5��
void Create_Yuangong(vector<Yuangong>& v){

	string nameseed = "ABCDE";
	for (int i = 0; i < 5;i++){
		Yuangong yg;
		yg.name = "Ա��";
		yg.name += nameseed[i];

		yg.age = rand() % 30;
		yg.salary = rand() % 10000 + 10000;
		yg.tele = "+86-88888888";

		v.push_back(yg);
	}

}
//��Ա��ָ�ɲ���
void Set_YG_Group(vector<Yuangong>& v, multimap<int, Yuangong>& group){
	
	for (vector<Yuangong>::iterator it = v.begin(); it != v.end(); it++){
		
		cout << "��ǰԱ����Ϣ:" << endl;
		cout << "����:" << it->name << " ���䣺" << it->age << " ����:" << it->salary << " �绰" << it->tele << endl;
		int departmentID = -1;
		while (true){
			
			cout << "�����벿��(1 ���۲� 2 ������ 3 ����) : " << endl;
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
				cout << "�������,����������:" << endl;
			}
		}
	}
}


//��ӡ������Ա����Ϣ
void Show_YG_Info(multimap<int, Yuangong>& group){
	
	int departmentID = -1;
	while (true){

		cout << "������Ҫ�鿴�Ĳ���(1 ���۲� 2 ������ 3 ����) : " << endl;
		scanf("%d", &departmentID);

		//��֤������Ч��
		if (departmentID < 1 || departmentID > 3){
			continue;
		}

		multimap<int, Yuangong>::iterator pos = group.find(departmentID);
		int ygcount =  group.count(departmentID);
		int num = 0;
		while (pos != group.end() && num < ygcount){
			cout << "����: " << pos->second.name << " ����:" << pos->second.age <<  " ����" << pos->second.salary << " �绰" << pos->second.tele <<  endl;
			num++;
			pos++;
		}
	
	}
}


int main(){

	//multimap ����
	//��˾������Ƹ�� 5 ��Ա����5 ��Ա�����빫˾֮����Ҫָ��Ա�����Ǹ����Ź���
	//��Ա��Ϣ��: ���� ���� �绰 ���ʵ����
	//ͨ�� Multimap ������Ϣ�Ĳ��� ���� ��ʾ
	//�ֲ�����ʾԱ����Ϣ ��ʾȫ��Ա����Ϣ

	vector<Yuangong> v;  //��Ա����Ϣ δ����֮ǰ
	multimap<int, Yuangong> Ygroup;  //��ŷ�����Ա����Ϣ
	Create_Yuangong(v); //����Ա��
	Set_YG_Group(v, Ygroup); //Ա������
	Show_YG_Info(Ygroup); //��������ʾԱ����Ϣ

	system("pause");
	return EXIT_SUCCESS;
}
