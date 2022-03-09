//loj143 
// prime test
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;


/*O(sqrt(n))*/
bool is_prime(ll x)
{
    if(x < 2) return false;
    for(ll i = 2; i <= x / i; ++i)
        if(x % i == 0) return false;
    return true;
}

inline ll qmul(ll a, ll b, ll p) { return (ll)((__int128)a * b % p); }

ll qpow(ll a, ll b, ll p)
{
    ll res = 1;
    while(b) {
        if(b & 1)
            res = qmul(res, a, p);
        a = qmul(a, a, p);
        b >>= 1;
    }
    return res;
}
const int test_time = 8;

bool mr_test(ll n)
{
    if(n < 3 || n % 2 == 0)  return n == 2;
    ll a = n - 1, b = 0;
    while(a % 2 == 0)  a /= 2, ++b;

    for (int i = 1, j; i <= test_time; ++i) 
    {
        ll x = rand() % (n - 2) + 2, v = qpow(x, a, n);
        if(v == 1)  continue;
        for (j = 0; j < b; ++j)
        {
            if(v == n - 1) break;
            v = qmul(v, v, n);
        }
        if(j >= b) return 0;
    }
    return 1;
}

int main()
{
    srand(time(0));
    ll x;
    while(cin >> x)
    {
        if(mr_test(x)) puts("Y");
        else puts("N");
    }

    return 0;
}