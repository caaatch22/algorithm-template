//求组合数的几种方法
//不确定的时候都开 long long
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7, N = 1e6 + 10;
//C(a, b) a上b下

/*1. 依照定义   当a, b很小的时候（几十）*/
int C(ll a, int b) // a上b下
{   
    if(a < b) return 0;
    int up = 1, down = 1;
    for (ll i = a; i > a - b; i -- ) up = i % mod * up % mod; //up *= i
    for (int j = 1; j <= b; j ++) down = (ll)j * down % mod; // down *= j
    return (ll)up * qpow(down, mod - 2) % mod; //   (up/down)
}

/*2. 递推 杨辉三角  a, b在2000这个数量级*/
//O(N^2) 1e6~1e7
void init()
{
    for (int i = 0; i < N; i ++)
        for (int j = 0; j <= i; j ++)
            if(!j) C[i][j] = 1;
            else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
}

//最常用
/*3. 预处理fac[], invfac[]*/
/**
 * //调用 :
 * 1ll * fac[b] * invfac[a] % mod * invfac[b - a] % mod;
 */
// O(N) 1e6左右 看N大小
int fac[N], invfac[N];
void init()
{
    fac[0] = 1;
    for (int i = 1; i < N; i ++)  (ll)fac[i] = fac[i - 1]*i% mod;
    invfac[N - 1] = qpow(fac[N - 1], mod - 2);
    for (int i = N - 2; i >= 0; i --)
        invfac[i] = (ll)invfac[i + 1] * (i + 1) % mod;
}

/*4. lucas定理 当a, b的值特别大 如1e9以上...1e18等*/
int C(int a, int b)
{
    int res = 1;
    for (int i = 1, j = a; i <= b; i ++, j --)
    {
        res = (ll)res * j % p;
        res = (ll)res * binpow(i, p - 2) % p;
    }
    return res;
}

ll lucas(ll a, ll b)
{//p为质数
    if(a < p && b < p) return C(a, b);
    return (ll)C(a % p, b % p) * lucas(a / p, b / p) % p;
}

