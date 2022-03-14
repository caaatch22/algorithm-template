//求n!的质因子  n~1e6
#include <bits/stdc++.h>
using namespace std;

//1筛出[1, 1e6]中的质数

const int N = 1e6 + 10;
typedef long long ll;
int p, n, vis[N], prime[N];

inline void getprime(int n){
    for (int i = 2; i <= n; i++){
        if(!vis[i]){
            prime[++p] = i;
            if((ll)i*i<=n)
            for (int j = i * i; j <= n; j+=i){
                vis[j] = 1;
            }
        }
    }
}

int main()
{
    cin >> n;
    getprime(n);
    // for (int i = 1; i <= p; i ++)
    // {
    //     int exp = 0, p = prime[i];
    //     for (int j = p; j <= n; j *= p)
    //     {
    //         exp += n / j;
    //         if((ll)j*p > n) break;
    //     }
    //     cout << p << ' ' << exp << '\n';
    // }
    for (int i = 1; i <= p; i ++)
    {
        int exp = 0, p = prime[i];
        for (int j = n; j ; j/= p)    exp += j / p;
        cout << p << ' ' << exp << '\n';
    }       
    return 0;
}