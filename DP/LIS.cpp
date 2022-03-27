//最长上升子序列

//1. n^2做法
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int f[N], a[N], n;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i ++)  cin >> a[i];
    
    for(int i = 1; i <= n; i ++)
    {
        f[i] = 1;
        for(int j = 1; j < i; j ++)
            if(a[j] < a[i]) f[i] = max(f[i], f[j] + 1);
    }
    
    int res = 0;
    for(int i = 1; i <= n; i ++)  res = max(res, f[i]);
    cout << res;
    
    return 0;
}

//2. 维护类似单调递增的队列

int q[N];

int main()
{
    cin >> n;
    for (int i = 0; i < n; i ++) cin >> a[i];

    int pos = 0;
    q[0] = a[0];

    for (int i = 1; i < n; i++)
    {
        if(a[i] > q[pos])
            q[++pos] = a[i];
        else
            *lower_bound(q, q + pos + 1, a[i]) = a[i];
    }

    cout << pos + 1;

    return 0;
}