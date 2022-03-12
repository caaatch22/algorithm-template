#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define int long long
const int N = 2e5 + 10, inf = 1e9 + 10;
int n, a[N], b[N];
int clo_al = 1e9 + 1, clo_bl = 1e9 + 1, clo_ar = 1e9 + 1, clo_br = 1e9 + 1;

void init()
{
    clo_al = clo_ar = clo_br = clo_bl = inf;
}


signed main()
{
    int T; scanf("%lld", &T);
    while(T -- )
    {
        scanf("%lld", &n);
        init();
        for (int i = 1; i <= n; i++)     scanf("%lld", &a[i]);
        for (int i = 1; i <= n; i++)     scanf("%lld", &b[i]);

        int ll = abs(a[1] - b[1]), lr = abs(a[1] - b[n]);

        int rl = abs(a[n] - b[1]), rr = abs(a[n] - b[n]);
        for (int i = 2; i <= n - 1; i ++)
        {
            clo_al = min(clo_al, abs(a[1] - b[i]));
            clo_ar = min(clo_ar, abs(a[n] - b[i]));
            clo_bl = min(clo_bl, abs(a[i] - b[1]));
            clo_br = min(clo_br, abs(a[i] - b[n]));
        }

        int res = 0;
        int c1 = ll + rr, c2 = lr + rl, c3 = 
        // res = min(abs(a[1] - b[n]) + abs(a[n] - b[1]), min(resl + resr, clo_al + clo_ar + clo_br + clo_bl));
        cout << res << '\n';
    }

    return 0;
}