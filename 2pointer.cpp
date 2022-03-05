// acwing 799
//最长连续不重复子序列长度
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, a[N], w[N];

int main()
{
    cin >> n;
    int res = 0;
    for (int i = 0; i < n; i ++)  cin >> a[i];

    for(int i = 0, j = 0; i < n; i ++)
    {
        w[a[i]] ++;
        while(j < n && w[a[i]] > 1)
        {
            w[a[j]]--;
            j ++;
        }
        res = max(res, i - j + 1);
    }
    cout << res;
    return 0;
}