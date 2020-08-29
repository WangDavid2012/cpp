#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<algorithm>
using namespace std;


//ѡ����
class Player{
public:
	Player(string name, int score) :name(name), score(score){}
	string name;
	int score; //����
};


//����ѡ��
void Create_Player(vector<Player>& v){

	string nameseed = "ABCDE";
	for (int i = 0; i < 5;i++){
		string name = "ѡ��";
		name += nameseed[i];
		Player p(name,0);  //����ѡ��
		v.push_back(p);
	}
}

//���
bool mycompare(int v1,int v2){
	if (v1 > v2){  //�Ӵ�С
		return true;
	}
	else{
		return false;
	}
}
void Set_Player_Score(vector<Player>& plist){
	
	for (vector<Player>::iterator it = plist.begin(); it != plist.end();it++){
		
		deque<int> dscore;
		for (int i = 0; i < 10;i++){
			int score = 50 + rand() % 50; //���
			dscore.push_back(score);
		}
		
		//���� sort
		sort(dscore.begin(), dscore.end(), mycompare);
		/*
				for (deque<int>::iterator it = dscore.begin(); it != dscore.end();it ++){
			cout << *it << " ";
		}
		cout << endl;
		*/

		dscore.pop_front(); //ȥ����߷�
		dscore.pop_back(); //ȥ����ͷ�
		//�����ܽ�
		int totalscore = 0;
		for (deque<int>::iterator dit = dscore.begin(); dit != dscore.end(); dit++){
			totalscore += *dit;
		}

		int scoreavg = totalscore / dscore.size();
		(*it).score = scoreavg;
	}

}
//��ʾ5��ѡ�ֵ÷�
void Show_Player_Score(vector<Player>& plist){

	for (vector<Player>::iterator it = plist.begin(); it != plist.end(); it++){
		cout << "����:" << it->name << " ����:" << it->score << endl;
	}
	cout << endl;

}
int main(){


	vector<Player>  vPlayer;  //������ǵ�ѡ����Ϣ
	Create_Player(vPlayer); //����ѡ��
	Set_Player_Score(vPlayer);
	Show_Player_Score(vPlayer);

	//��ί��ְ���(sort �㷨����)
	//���� 5 ��ѡ��(�������÷�)��10 ����ί�� 5 ��ѡ�ֽ��д��
	//�÷ֹ���ȥ����߷֣�ȥ����ͷ֣�ȡ��ƽ����
	//���÷ֶ� 5 ��ѡ�ֽ�������

	system("pause");
	return EXIT_SUCCESS;
}
