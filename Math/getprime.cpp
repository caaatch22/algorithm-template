#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e7 + 10;
int primes[N], cnt;
bool vis[N]; //合数true
int n, q;
//linear
void get_prime(int n) {
	for(int i = 2; i <= n; i ++) {
    	if(!vis[i]) primes[ ++ cnt] = i;
    	for(int j = 1; j <= cnt && i * primes[j] <= n; ++ j) {
        	vis[i * primes[j]] = 1;
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
            primes[++cnt] = i;
            if((ll)i*i<=n)
            for (int j = i * i; j <= n; j+=i){
                isprime[j] = 0;
            }
        }
    }
}
