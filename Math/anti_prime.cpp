//c27E
//反素数 https://codeforces.com/problemset/problem/27/E

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

int p[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
const ll inf = 0x3f3f3f3f3f3f3f3f;

ll res;
int n;

//up:上一个质因子的幂，不会超过64
//curnum:当前数（更新res）, cnt：当前curnum对应的因子数
void dfs(ll curnum, int cnt,int idx, int up)
{
    if(cnt > n || idx >= 16)  return;
    if(cnt == n && res > curnum) {
        res = curnum;
        return;
    }

    for (int i = 1; i <= up; i++)
    {
        if(curnum / p[idx] > res) break;
        curnum *= p[idx];
        dfs(curnum, cnt * (i + 1), idx + 1, i + 1);
    }
}


int main()
{
    while(~scanf("%d", &n))
    {
        res = inf;
        dfs(1, 1, 0, 64);
        printf("%lld\n", res);
    }
    
    return 0;
}