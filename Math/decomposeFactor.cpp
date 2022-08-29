//acwing 867
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
vector<pair<int, int>> pfac[N];
//预处理质因数（当需要经常1~N所有数的质因数时候）
void init() {
    for (int i = 2; i < N; i ++) {
        if(pfac[i].size()) continue;
        for (int j = i; j < N; j += i) {
            int t = j, cnt = 0;
            while(t%i == 0)  t/= i, cnt ++;
            pfac[j].push_back({i, cnt});
        }
    }
}

//根号n算法（n为数值大小）
void decompose(int n) {
    for (int i = 2; i <= n / i; i ++)
        if(n % i == 0) //then i is prime
        {
            int s = 0;
            while(n%i == 0)  {
                n /= i;
                s++;
            }
            printf("%d %d\n", i, s);
        }
    if(n > 1)  printf("%d %d\n", n, 1);
    puts("");
}


//log(n)算法 利用最小质因数筛
//先用欧拉筛筛出一定数值内的所有数字的质因子
//同时维护一个minp[i]表示i的最小质因子
//用的时机： 一般求n个数每个数的质因子
//          且数值域大于预处理质因子所能承受范围 >1e5,
//          而又小于线性筛所能承受范围           <1e8
// http://oj.daimayuan.top/course/10/problem/733 例题（需要稍加改进）
int primes[N], minp[N], vis[N];
void get_prime(int n) {
    int pcnt = 0;
    for(int i = 2; i <= n; i ++) {
    	if(!vis[i]) primes[ ++ pcnt] = i, minp[i] = i;
    	for(int j = 1; j <= pcnt && i * primes[j] <= n; ++ j) {
        	vis[i * primes[j]] = 1;
            minp[primes[j] * i] = primes[j];
            if(i % primes[j] == 0) break;
    	}
    }
}

void decompose_log(int n) {
    int cnt = 0;
    while (n > 1) {
        int t = minp[n];
        int cnt = 0;
        while (n % t == 0) {
            cnt++;
            n /= t;
        }
        printf("%d %d\n", t, cnt);
    }
}

int main() {
    int n;  cin >> n;
    while(n --) {
        int x;
        cin >> x;
        decompose(x);
    }
    return 0;
}