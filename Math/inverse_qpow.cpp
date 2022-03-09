#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll qpow(ll a, ll b, ll p)
{
    ll res = 1;
    while(b)
    {
        if(b & 1)
            res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}


int main()
{
    int n;
    cin >> n;
    while(n -- )
    {
        int a, p;
        cin >> a >> p;
        int res = qpow(a, p - 2, p);
        if(a % p)
            cout << res << '\n';
        else
            puts("impossible");
    }
    return 0;
}