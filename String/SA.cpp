//p4051 
//SA数组寻找最小循环移动位置
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
char s[N], a[N], ans[N >> 1];
int n, w, sa[N], rk[N << 1], oldrk[N << 1];
int ht[N];

void init_sa() {
    for (int i = 1; i <= n; i ++)    sa[i] = i, rk[i] = s[i];
    for (int w = 1; w < n; w <<= 1) {
        sort(sa + 1, sa + n + 1,
             [&](int x, int y)
             { return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y]; });
        memcpy(oldrk, rk, sizeof(rk));
        for (int i = 1, p = 0; i <= n; ++i) {
            if(oldrk[sa[i]] == oldrk[sa[i - 1]] &&  oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
                rk[sa[i]] = p;
            else
                rk[sa[i]] = ++p;
        }
    }
}

// ht[i] = lcp(sa[i], sa[i - 1])
inline void init_ht() {
    for (int i = 1, k = 0; i <= n; ++i) {
        if (rk[i] == 0) continue;
        if (k) --k;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
        ht[rk[i]] = k;
    }
}

int main() {
    scanf("%s", a + 1);
    n = strlen(a + 1);
    int i;
    for (i = 1; i <= n; i ++)   s[i] = a[i];
    for (i = n + 1; i <= n + n; i ++)   s[i] = a[i - n];
    s[i] = '\0';
    n = strlen(s + 1);

    init_sa();
    int len = n >> 1;

    for (int i = 1; i <= n; i ++) 
        if(sa[i] <= len)
            putchar(s[(sa[i] + len - 1)]);

    return 0;
}