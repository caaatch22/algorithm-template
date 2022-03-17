//p1502
//经典的线段树扫描线算法
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e4 + 10;
struct L
{
    ll x, y1, y2;
    ll c;
    //当左矩形的右边界与右矩形的左边界重合时， 该线上的点应属于能被两个窗户都能看见的状态所以先加
    bool operator<(const L &rhs) const { return x == rhs.x ? c < rhs.c : x < rhs.x; }
}line[2 * N];

ll n, w, h, m;
ll b[2 * N]; //离散化前的y轴

struct node
{
    ll l, r;
    ll maxv, add;
} t[8 * N];


void pushdown(ll p)
{
    node &root = t[p], &nl = t[p << 1], &nr = t[p << 1 | 1];
    if(root.add)
    {
        nl.add += root.add, nl.maxv += root.add;
        nr.add += root.add, nr.maxv += root.add;
        root.add = 0;
    }
}

void pushup(ll p)
{
    t[p].maxv = max(t[p << 1].maxv, t[p << 1 | 1].maxv);
}

void modify(ll p, ll l, ll r, ll c)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].maxv += c;
        t[p].add += c;
        return;
    }
    else
    {
        pushdown(p);
        ll mid = t[p].l + t[p].r >> 1;
        if(l <= mid)  modify(p << 1, l, r, c);
        if(r > mid) modify(p << 1 | 1, l, r, c);
        pushup(p);
    }
}

void build(ll p, ll l, ll r)
{
    if(l == r)
    {
        t[p] = {l, r, 0, 0};
        return;
    }

    t[p].l = l, t[p].r = r;
    ll mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    //pushup(p);//初始化都是0不用pushup()
}

/*
int main()//acw上的格式
{
    while(~scanf("%lld%lld%lld", &n, &w, &h))
    {
        memset(line, 0, sizeof(line));
        memset(b, 0, sizeof(b));
        memset(t, 0, sizeof(t));
        
        for (ll i = 1, j = 0; i <= n; i++)
        {
            ll x, y;
            ll l;
            scanf("%lld%lld%lld", &x, &y, &l);
            line[i] = {x, y, y + h - 1, l};
            line[i + n] = {x + w - 1, y, y + h - 1, -l};
            b[ ++ j] = y;
            b[ ++ j] = y + h - 1;
        }
        n <<= 1;
        sort(b + 1, b + 1 + n);
        m = unique(b + 1, b + 1 + n) - b - 1;//unique得到end()迭代器
        sort(line + 1, line + 1 + n);

        build(1, 1, m - 1);

        for (ll i = 1; i <= n; i++) 
        {
            line[i].y1 = lower_bound(b + 1, b + m + 1, line[i].y1) - b - 1;
            line[i].y2 = lower_bound(b + 1, b + m + 1, line[i].y2) - b - 1;
        }

        
        ll res = 0;
        for (ll i = 1; i <= n; i++)
        {
            modify(1, line[i].y1,line[i].y2 - 1, line[i].c);
            res = max(res, t[1].maxv);
        }

        printf("%lld\n", res);
    }    
    return 0;
}
*/


int main()//luogu上的格式
{

    ll T;
    scanf("%lld", &T);
    while( T -- )
    {
        memset(line, 0, sizeof(line));
        memset(b, 0, sizeof(b));
        memset(t, 0, sizeof(t));

        scanf("%lld%lld%lld", &n, &w, &h);
        for (ll i = 1, j = 0; i <= n; i++)
        {
            ll x, y, l;
            scanf("%lld%lld%lld", &x, &y, &l);
            line[i] = {x, y, y + h - 1, l};
            line[i + n] = {x + w - 1, y, y + h - 1, -l};
            b[ ++ j] = y;
            b[ ++ j] = y + h - 1;
        }
        n <<= 1;
        sort(b + 1, b + 1 + n);
        m = unique(b + 1, b + 1 + n) - b - 1;//unique得到end()迭代器
        sort(line + 1, line + 1 + n);

        for (ll i = 1; i <= n; i++)
        {
            line[i].y1 = lower_bound(b + 1, b + m + 1, line[i].y1) - b - 1;
            line[i].y2 = lower_bound(b + 1, b + m + 1, line[i].y2) - b - 1;
        }
        build(1, 1, m - 1);

        ll res = 0;
        for (ll i = 1; i <= n; i++)
        {
            modify(1, line[i].y1, line[i].y2, line[i].c);
            res = max(res, t[1].maxv);
        }

        printf("%d\n", res);
    }
    return 0;
}
