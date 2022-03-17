//对询问离线+树状数组
//维护区间上的种类
#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
struct querys {
    int l, r, idx;
    bool operator<(const querys &rhs) const { return r == rhs.r ? l < rhs.l : r < rhs.r; }
} qs[N];

int n, tr[N], m, a[N], ans[N], vis[N];
int lowbit(int x) { return x & -x; }
void modify(int x, int v)
{
    for (int i = x; i <= n; i += lowbit(i))
        tr[i] += v;
}

int sum(int x)
{
    int res = 0;
    for (int i = x; i; i-= lowbit(i))
        res += tr[i];
    return res;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++)    scanf("%d", &a[i]);

    scanf("%d", &m);
    for (int i = 1; i <= m; i ++)
    {
        scanf("%d%d", &qs[i].l, &qs[i].r);
        qs[i].idx = i;
    }
    sort(qs + 1, qs + 1 + m);

    int last = 1;
    for (int i = 1; i <= m; i ++)
    {
        for (int j = last; j <= qs[i].r; j ++)
        {
            if(vis[a[j]])  modify(vis[a[j]], -1);
            modify(j, 1);
            vis[a[j]] = j;
        }
        last = qs[i].r + 1;
        ans[qs[i].idx] = sum(qs[i].r) - sum(qs[i].l - 1);
    }

    for (int i = 1; i <= m; i ++)    printf("%d\n", ans[i]);

    return 0;
}