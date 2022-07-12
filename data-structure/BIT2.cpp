/**
 * bit的其他应用 （一般都是根据数值范围建立bit）
 * 1. 逆序对
 */

//区间覆盖一个新的种类（不会掩盖已有属性）
//询问区间总共有多少属性
//luogu2184  差分思想
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
int tr1[N], tr2[N], n, m;

int lowbit(int x) { return x & -x; }

void add(int tr[], int x, int k)
{
    for(int i = x; i <= n; i+= lowbit(i))   tr[i] += k;
}

int query(int tr[], int x)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
        res += tr[i];
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    while(m --)
    {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1)
        {
            add(tr1, l, 1);
            add(tr2, r, 1);
        }
        else
            printf("%d\n", query(tr1, r) - query(tr2, l - 1));
    }
    return 0;
}