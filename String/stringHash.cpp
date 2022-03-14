#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int N = 1010, base = 131;
int n, m, q, l, r;
char s[N], t[N];
ull h[N], p[N], ht[N];

ull get(int l, int r) { return h[r] - h[l - 1] * p[r - l + 1]; }

int main()
{
    cin >> n >> m >> q;
    cin >> s + 1 >> t + 1;
    p[0] = 1;
    for (int i = 1; i <= n; i ++)
    {
        p[i] = p[i - 1] * base;
        h[i] = h[i - 1] * base + s[i] - '0';
    }

    for (int i = 1; i <= m; i++)
        ht[i] = ht[i - 1] * base + t[i] - '0';

    ull tmp = ht[m] - ht[0] * p[m - 0 + 1];
    while(q -- )
    {
        ll res = 0;
        cin >> l >> r;
        for (int i = l; i <= r - m + 1; i ++)
            if (get(i, i + m - 1) == tmp) res++;

        cout << res << '\n';
    }

    return 0;
}