//区间dp1
//枚举长度，左右端点，区间内值
#include <bits/stdc++.h>
using namespace std;

const int N = 220;
int n, w[N], f[N][N];

int main()
{
    
    cin >> n;
    for(int i = 1; i <= n; i ++)  cin >> w[i], w[i + n] = w[i];
    
    for(int len = 2; len <= n + 1; len ++)
    {
        for(int l = 1; l + len - 1 <= 2 * n; l ++)
        {
            int r = len + l - 1;
            for(int k = l + 1; k < r; k ++)
                f[l][r] = max(f[l][r], f[l][k] + f[k][r] + w[r]*w[l]*w[k]);
        }
    }
    int res = 0;
    for(int l = 1; l <= n; l++)
        res = max(res, f[l][l + n]);
    cout << res;
    
    return 0;
}