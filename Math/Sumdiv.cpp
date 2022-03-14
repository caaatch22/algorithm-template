#include <iostream>
#include <algorithm>
#include <unordered_map>
#define fi first
#define se second
using namespace std;

typedef long long ll;
const int N = 5e7 + 10, mod = 9901;
int a, b;

int qpow(ll a, ll b) {
    int res = 1;
    while(b) {
        if(b&1) res = (ll)res * a % mod;
        b >>= 1;
        a = (ll)a * a % mod;
    }
    return res;
}

unordered_map<int, int> primes;

void divide(int n)
{
    for(int i = 2; i <= n/i; i ++) 
        while(n%i == 0) n/=i, primes[i]++;
    if(n > 1) primes[n] ++;
}

int main()
{
    int res = 1;
    cin >> a >> b;
    divide(a);   
    if(a == 0) { cout << 0; return 0;}
    for(auto p:primes) 
    {
        if((p.fi - 1) % mod == 0) 
        {
            res = ((ll)b*p.se + 1) % mod * res % mod;
            continue;
        }
        int x = qpow(p.fi, (ll)b*p.se + 1);
        x = (x - 1 + mod) % mod;
        int y = p.fi - 1;
        y = qpow(y, mod - 2);
        res = (ll)res * x % mod * y % mod;
    }
    cout << res;
 
    return 0;
}