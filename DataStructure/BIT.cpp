/*
//树状数组写区间修改，单点查询
int a[N], b[N], tr[N], n, m;
//b[]是a[]的差分数组
int lowbit(int x) {return x & -x;}

int query(int x)
{
    int res = 0;
    fro(int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

void add(int x, int val)
{
    for(int i = x; i <= n; i += lowbit(i))
        tr[i] += val;
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i ++)
    {
        cin >> a[i];
        b[i] = b[i - 1] + a[i];
    }

    for(itn i = 1; i <= n; i ++)
        add(i, b[i]);
    
}

*/

//BIT写区间修改，区间查询
//记录两个数组 b[i] = a[i] - a[i - 1]; c[i] = i * b[i];

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

int a[N], b[N];
ll t1[N], t2[N]; //维护b[i], b[i] * i的前缀和
int n, m;

void add(ll tr[], int x, ll c)
{
    for (int i = x; i <= n; i += lowbit(i))
        tr[i] += c;
}

ll query(ll tr[], int x)
{
    ll res = 0;
    for (int i = x; i; i-= lowbit(i))
        res += tr[i];
    return res;
}

ll preSum(int x) { return query(t1, x) * (x + 1) - query(t2, x); }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i<=n; i++) scanf("%d", &a[i]);

    for (int i = 1; i <= n; i++)
    {
        int b = a[i] - a[i - 1];
        add(t1, i, b);
        add(t2, i, (ll)b * i);
    }

    while(m -- )
    {
        char op[2];
        int l, r, d;
        scanf("%s%d%d", op, &l, &r);
        if( *op == 'Q')
            printf("%lld\n", preSum(r) - preSum(l - 1));
        else
        {
            scanf("%d", &d);
            //a[l] += d;
            add(t1, l ,d), add(t2, l, l * d);
            add(t1, r + 1, -d), add (t2, r + 1, (r + 1) * -d);
        }
    }

    return 0;
}