//p2504
#include <bits/stdc++.h>
using namespace std;

const int N = 1010, M = 1e6 + 10;

typedef long long ll;
struct Edge{
    int u, v;
    ll w;
    bool operator<(const Edge &rhs) const { return w < rhs.w; }
} edges[M];
int cnt;
pair<int, int> ord[N];
int n, m, a[510];

int fa[M];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

ll get(int i, int j)
{
    return (ll)(ord[i].first - ord[j].first) *(ord[i].first - ord[j].first) 
           + (ll)(ord[i].second - ord[j].second) *(ord[i].second - ord[j].second);
}

main()
{
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &a[i]), a[i] *= a[i];
    sort(a + 1, a + 1 + m);

    scanf("%d", &n);
    for (int i = 1; i <= n; i ++)
    {
        int x, y; scanf("%d %d", &x, &y);
        ord[i] = {x, y};
    }

    for (int i = 1; i <= n; i ++)
        for (int j = i + 1; j <= n; j ++)
            edges[++cnt] = {i, j, get(i, j)};

    for (int i = 1; i <= cnt; i++)  fa[i]= i;
    sort(edges + 1, edges + cnt + 1);

    ll res = 0;
    for (int i = 1; i <= cnt; i ++)
    {
        int u = edges[i].u, v = edges[i].v;
        if(find(u) != find(v))
        {
            fa[find(u)] = find(v);
            res = max(res, edges[i].w);
        }
    }

    int t = lower_bound(a + 1, a + m + 1, res) - a;
    cout << m - t + 1;
    return 0;
}