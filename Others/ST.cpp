//ST表
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int f[N][21], n, m;
int a[N];
//f[i][j]表示区间[i, i + 2^j - 1]的最大值

void init_st() {
    // cout << __lg(N) << endl;3
    for (int j = 0; j < 21; j ++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)//区间长度是2^j所以要减一
            if(!j)  f[i][j] = a[i];
            else
                f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
}

int query(int l, int r) {
    int len = r - l + 1;
    int k = __lg(len);
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}

int main() {

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    init_st();

    while(m -- ) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r));
    }

    return 0; 
}
