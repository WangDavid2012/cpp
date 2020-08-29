#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<deque>
#include<numeric>
#include<functional>
using namespace std;

//����ѡ����
class Speaker{
public:
	string name;
	int score[3];
};


//����ѡ��
void Create_Speaker(map<int, Speaker>& mapSpeaker, vector<int>& v1){


	string nameseed = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < 24;i++){
		
		//����ѡ�ֶ���
		Speaker speaker;
		speaker.name = "ѡ��";
		speaker.name += nameseed[i];

		speaker.score[0] = 0;
		speaker.score[1] = 0;
		speaker.score[2] = 0;

		//����ѡ��Ψһ�Ĳ������
		int SpeakerID = 100 + i;
		mapSpeaker.insert(make_pair(SpeakerID, speaker)); //����ѡ����Ϣ
		v1.push_back(SpeakerID);
	}


}

//ѡ�ֳ�ǩ
void Random_SpeakerID(vector<int>& v1){
	random_shuffle(v1.begin(),v1.end());
}

//ѡ�ֱ���
void Match_Speaker(int index, vector<int>& v1, map<int, Speaker>& mapSpeaker, vector<int>& v2){

	multimap<int, int , greater<int> > mapGroup;
	int indexTemp = 0;
	int indexGroup = 0;
	for (vector<int>::iterator it = v1.begin(); it != v1.end();it++){
		
		indexTemp++;

		deque<int> dscore;  //������ί10�ε÷�
		for (int i = 0; i < 10;i++){
			int score = 50 + rand() % 50;
			dscore.push_back(score); 
		}
		//����
		sort(dscore.begin(),dscore.end()); //��С��������
		//ȥ����߷� ȥ����ͷ�
		dscore.pop_back();//ȥ����߷�
		dscore.pop_front();//ȥ����ͷ�

		int totalscore = accumulate(dscore.begin(), dscore.end(),0);
		int scoreavg = totalscore / dscore.size();

		mapSpeaker[*it].score[index - 1] = scoreavg; //���浱ǰ����ѡ�ֵĵ÷�
		mapGroup.insert(make_pair(scoreavg,*it)); //���������Ϣ

		if (indexTemp % 6 == 0){
			indexGroup++;
			int highIndex = 0;
			printf("��%d�ֱ�����%d������ɼ�:\n", index, indexGroup);
			for (multimap<int, int, greater<int> >::iterator it = mapGroup.begin(); it != mapGroup.end();it ++){
				highIndex++;
				if (highIndex <= 3){
					v2.push_back(it->second);
				}
				cout << "����:" << mapSpeaker[it->second].name << " ����:" << mapSpeaker[it->second].score[index - 1] << endl;
			}
			
			mapGroup.clear(); //���mapGroup
		}

	}


}

//�鿴�������
void Show_Match_Result(int index, vector<int>& v2, map<int, Speaker>& mapSpeaker){

	printf("��%d�ֱ�����������:\n",index);
	for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++){
		cout << "����:" << mapSpeaker[*it].name << " ����:" << mapSpeaker[*it].score[index - 1] << endl;
	}

}

int main(){

	map<int, Speaker> mapSpeaker; //����ѡ�ֵ���Ϣ ���ݱ��

	vector<int> v1; //�����һ�ֲ������
	vector<int> v2; //��һ�ֱ����Ľ������
	vector<int> v3; //����ڶ��ֱ�����������
	vector<int> v4; //�������յ�ǰ�����ı��


	//����ѡ�� 24��
	Create_Speaker(mapSpeaker, v1);
	
	//��һ�ֱ���
	Random_SpeakerID(v1);//ѡ�ֳ�ǩ
	Match_Speaker(1, v1, mapSpeaker,v2);//ѡ�ֱ���
	Show_Match_Result(1, v2, mapSpeaker);//�鿴�������

	//�ڶ��ֱ���
	Random_SpeakerID(v2);//ѡ�ֳ�ǩ
	Match_Speaker(2, v2, mapSpeaker,v3);//ѡ�ֱ���
	Show_Match_Result(2, v3, mapSpeaker);//�鿴�������

	//�����ֱ���
	Random_SpeakerID(v3);//ѡ�ֳ�ǩ
	Match_Speaker(3, v3, mapSpeaker, v4);//ѡ�ֱ���
	Show_Match_Result(3, v4, mapSpeaker);//�鿴�������



	system("pause");
	return EXIT_SUCCESS;
}
