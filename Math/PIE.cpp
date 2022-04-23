//cf451E acwing214
/**
 * S = {n1*a1, n2*a2 ... nk*ak}
 * 从中取出r个元素产生不同多重集的数量
 * 
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7, N = 20;
ll A[N], n, m;

int qpow(int a, int b) {
    int res = 1;
    while(b) {
        if(b&1) res = (ll)res*a % mod;
        b >>= 1;
        a = (ll)a * a % mod;
    }
    return res;
}

int C(ll a, int b) // a上b下
{   
    if(a < b) return 0;
    int up = 1, down = 1;
    for (ll i = a; i > a - b; i -- ) up = i % mod * up % mod;
    for (int j = 1; j <= b; j ++) down = (ll)j * down % mod;
    return (ll)up * qpow(down, mod - 2) % mod;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i ++)  cin >> A[i];

    int res = 0;
    for (int i = 0; i < 1 << n; i ++)
    {
        ll a = m + n - 1, b = n - 1;
        int sign = 1;
        for (int j = 0; j < n; j ++)
        {
            if(i >> j & 1)
            {
                sign *= -1;
                a -= A[j] + 1;
            }
        }
        res = (res + C(a, b) * sign) % mod;
    }
    cout << (res + mod) % mod;

    return 0;
}