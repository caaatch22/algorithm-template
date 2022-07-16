#include<bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10;
int n, a[N], pos[N], st[N], ed[N], add[N];

void init(int n) {
    int t = sqrt(n);
    for (int i = 1; i <= t; i ++) {
        st[i] = (i - 1) * t + 1;
        ed[i] = i * t;
    }
    if(ed[t] < n)
        t++, st[t] = ed[t - 1] + 1, ed[t] = n;

    for (int i = 1; i <= t; i ++)
        for (int j = st[i]; j <= ed[i]; j ++)
            pos[j] = i;
}

void modify(int l, int r, int c) {
    int p = pos[l], q = pos[r];
    if(p == q) {
        for (int i = l; i <= r; i ++)  a[i] += c; 
    }
    else  {
        for (int i = l; i <= ed[p];  i++)    a[i] += c;
        for (int i = st[q]; i <= r; i ++)    a[i] += c;

        for (int i = p + 1; i <= q - 1; i ++)
            add[i] += c;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++)    scanf("%d", &a[i]);

    init(n);

    for (int i = 1; i <= n; i ++) {
        int op, l, r, c;
        scanf("%d%d%d%d", &op, &l, &r, &c);
        if(!op)
            modify(l, r, c);
        else
            printf("%d\n", a[r] + add[pos[r]]);
    }
    return 0;
}