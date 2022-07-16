#include <bits/stdc++.h>
using namespace std;
const int N = 50010;
int mu[N], p[N]; // p为素数数组
bool flg[N];
void init() {
    int tot = 0;  mu[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!flg[i]) {
            p[++tot] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= tot && i * p[j] < N; ++j) {
            flg[i * p[j]] = 1;
            if (i % p[j] == 0) {
                mu[i * p[j]] = 0;
                break;
            }
            mu[i * p[j]] = -mu[i];
        }
    }
    // 常用mu前缀和
    // for (int i = 1; i <= N; ++i) mu[i] += mu[i - 1];
}
