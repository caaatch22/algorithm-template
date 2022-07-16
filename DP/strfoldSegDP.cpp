//scoi2003字符串折叠
#include <bits/stdc++.h>
using namespace std;
const int N = 110;
char s[N];
int nxt[N], f[N][N];

int cal(int x) {
    int res = 0;
    while(x) {
        res++;
        x /= 10;
    }
    return res;
}

int dp(int l, int r) {
    if(f[l][r] != -1)  return f[l][r];
    if(l == r)   return f[l][r] = 1;

    f[l][r] = 0x3f3f3f3f;
    for (int k = l; k < r; k ++)
        f[l][r] = min(f[l][r], dp(l, k) + dp(k + 1, r));

    nxt[l] = 0;
    for (int i = l + 1; i <= r; i ++) {
        int j = nxt[i - 1];
        while(j && s[i] != s[l + j])   j = nxt[l + j - 1];
        if(s[i] == s[j + l])  j++;
        nxt[i] = j;
    }
    int len = r - l + 1;
    int period = len - nxt[r];
    if((len % period) == 0 )
        f[l][r] = min(f[l][r], dp(l, l + period - 1) + 2 + cal((len / period)));//cal:有可能是两位数等

    return f[l][r];
}

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    memset(f, -1, sizeof f);
    printf("%d\n", dp(1, n));
    return 0;
}