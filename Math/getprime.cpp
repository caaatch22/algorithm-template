#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e7 + 10; 
// minp[i]为i的最小素因子  http://oj.daimayuan.top/course/10/problem/733
int primes[N], pcnt, minp[N]; // 可用于log级别分解质因数
bool vis[N]; //合数true
int n, q;
//linear
void get_prime(int n) {
	for(int i = 2; i <= n; i ++) {
    	if(!vis[i]) primes[ ++ pcnt] = i, minp[i] = i;
    	for(int j = 1; j <= pcnt && i * primes[j] <= n; ++ j) {
        	vis[i * primes[j]] = 1;
            minp[primes[j] * i] = primes[j]; 
            if(i % primes[j] == 0) break;
    	}
    }
}

//about linear :O(nloglogn)
bool isprime[N];
inline void getprime(int n) {
    for (int i = 2; i <= n; i++) isprime[i] = 1;
    for (int i = 2; i <= n; i++) {
        if(isprime[i]) {
            primes[++pcnt] = i;
            if((ll)i*i<=n)
            for (int j = i * i; j <= n; j+=i){
                isprime[j] = 0;
            }
        }
    }
}
