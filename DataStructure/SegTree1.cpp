//线段树的单点修改区间查询
//相关应用（不涉及区间修改的）
/*
1. 维护区间上的最大值/最小值
2. 查询区间最大连续字段和   （维护lmax, rmax, tmax）
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int a[N], n, m;

struct node
{
    int l, r, maxv;
} t[N << 2];


void pushup(int p)
{
    t[p].maxv = max(t[p << 1].maxv, t[p << 1 | 1].maxv);
}

void modify(int p, int x, int val)
{
    if(t[p].l == t[p].r) {t[p] = {x, x, val}; return;}

    int mid = t[p].l + t[p].r >> 1;
    if(x <= mid) modify(p << 1, x, val);
    else modify(p << 1 | 1, x, val);
    pushup(p);
}

void build(int p, int l, int r)
{
    if(l == r) {t[p] = {l, r, a[l]} ;return; }

    t[p].l = l, t[p].r = r;
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

int query(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].maxv;
    int mid = t[p].l + t[p].r >> 1;
    
    if(r <= mid) return query(p << 1, l, r);
    else if(l > mid) return query(p << 1 | 1, l, r);
    else
        return max(query(p << 1, l, r), query(p << 1 | 1, l, r));
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)    scanf("%d", &a[i]);

    build(1, 1, n);
    while(m -- )
    {
        char op[2];
        int x, y;
        scanf("%s%d%d", op, &x, &y);
        if(*op == 'U')
        {
            if(a[x] < y)
                modify(1, x, y), a[x] = y;
        }
        else
            printf("%d\n", query(1, x, y));
    }
    return 0;
}