#include <map>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int b[] = { 2, 3, 6, 9, 11, 11, 11, 22, 32, 78 };


//ͳ��������a�ĸ���
int count_test1()
{
    int a;
    cin >> a;
    //count ����
    int ans = count(b, b + 8, a);
    cout << ans << endl;
    return 0;
}

bool cmp(int a)
{
    return a > 10;
}
//ͳ�ƴ���10�ĸ���
int count_test2()
{
    //ͳ�����������ļ���
    int ans = count_if(b, b + 8, cmp);
    cout << ans << endl;
    return 0;
}