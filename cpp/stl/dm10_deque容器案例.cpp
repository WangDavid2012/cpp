#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<algorithm>
using namespace std;


//选手类
class Player{
public:
	Player(string name, int score) :name(name), score(score){}
	string name;
	int score; //分数
};


//创建选手
void Create_Player(vector<Player>& v){

	string nameseed = "ABCDE";
	for (int i = 0; i < 5;i++){
		string name = "选手";
		name += nameseed[i];
		Player p(name,0);  //创建选手
		v.push_back(p);
	}
}

//打分
bool mycompare(int v1,int v2){
	if (v1 > v2){  //从大到小
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
			int score = 50 + rand() % 50; //打分
			dscore.push_back(score);
		}
		
		//排序 sort
		sort(dscore.begin(), dscore.end(), mycompare);
		/*
				for (deque<int>::iterator it = dscore.begin(); it != dscore.end();it ++){
			cout << *it << " ";
		}
		cout << endl;
		*/

		dscore.pop_front(); //去除最高分
		dscore.pop_back(); //去除最低分
		//分数总结
		int totalscore = 0;
		for (deque<int>::iterator dit = dscore.begin(); dit != dscore.end(); dit++){
			totalscore += *dit;
		}

		int scoreavg = totalscore / dscore.size();
		(*it).score = scoreavg;
	}

}
//显示5名选手得分
void Show_Player_Score(vector<Player>& plist){

	for (vector<Player>::iterator it = plist.begin(); it != plist.end(); it++){
		cout << "姓名:" << it->name << " 分数:" << it->score << endl;
	}
	cout << endl;

}
int main(){


	vector<Player>  vPlayer;  //存放我们的选手信息
	Create_Player(vPlayer); //创建选手
	Set_Player_Score(vPlayer);
	Show_Player_Score(vPlayer);

	//评委打分案例(sort 算法排序)
	//创建 5 个选手(姓名，得分)，10 个评委对 5 个选手进行打分
	//得分规则：去除最高分，去除最低分，取出平均分
	//按得分对 5 名选手进行排名

	system("pause");
	return EXIT_SUCCESS;
}
