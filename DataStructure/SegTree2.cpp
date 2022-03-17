//常见的区间维护
/**
 * 区间同时加上一个数，可以：
 * 1. 维护区间和
 * 2. 维护最大字段和
 * 3. 维护区间平方和
 */ 
/**
 * 区间修改成之指定数 维护sum, lazy(指定数值), bool changed即可
 */ 
/**
 * 区间内开根号：由于六次根号1e12（向下取整）
 * 即得到1， 所以可以暴力修改 p4145
 */
/**
 * 区间内数字同时乘以一个数
 * 如下：
 */

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
int n, m, mod;
int a[N];

struct node
{
    int l, r;
    int sum, add, mul;
} t[4 * N];

void eval(node &t, int add, int mul)
{
    t.sum = ((ll)t.sum * mul + (ll)(t.r - t.l + 1) * add) % mod;
    t.mul = (ll)t.mul * mul % mod;
    t.add = ((ll)t.add * mul + add) % mod;
}

void pushup(int p)
{
    t[p].sum = (t[p << 1].sum + t[p << 1 | 1].sum) % mod;
}

void pushdown(int p)
{
    eval(t[p << 1], t[p].add, t[p].mul);
    eval(t[p << 1 | 1], t[p].add, t[p].mul);

    t[p].add = 0, t[p].mul = 1;
}

void build(int p, int l, int r)
{
    if(l == r)
    {
        t[p] = {l, r, a[l], 0, 1};
        return;
    }

    t[p] = {l, r, 0, 0, 1};
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void modify(int p, int l, int r, int add, int mul)
{
    if(t[p].l >= l && t[p].r <= r)  eval(t[p], add, mul);
    else
    {
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if(l <= mid)  modify(p << 1, l, r, add, mul);
        if(r > mid)  modify(p << 1 | 1, l, r, add, mul);
        pushup(p);
    }
}

int query(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r)  return t[p].sum;

    pushdown(p);
    int res = 0;
    int mid = t[p].l + t[p].r >> 1;

    if(l <= mid) res += query(p << 1, l, r);
    if(r > mid)  res += query(p << 1 | 1, l, r);
    res %= mod;
    return res;
}

int main()
{
    scanf("%d%d", &n, &mod);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build(1, 1, n);

    scanf("%d", &m);
    while(m -- )
    {
        int op, l, r, d;
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1)
        {
            scanf("%d", &d);
            modify(1, l, r, 0, d);
        }
        else if(op == 2)
        {
            scanf("%d", &d);
            modify(1, l, r, d, 1);
        }
        else
            printf("%d\n", query(1, l, r));
    }
    return 0;
}
