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


//统计数组中a的个数
int count_test1()
{
    int a;
    cin >> a;
    //count 计数
    int ans = count(b, b + 8, a);
    cout << ans << endl;
    return 0;
}

bool cmp(int a)
{
    return a > 10;
}
//统计大于10的个数
int count_test2()
{
    //统计满足条件的计数
    int ans = count_if(b, b + 8, cmp);
    cout << ans << endl;
    return 0;
}