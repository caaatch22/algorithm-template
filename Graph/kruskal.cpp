//acwing859
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
struct edge
{
    int u, v, w;
    bool operator<(const edge &rhs) const { return w < rhs.w; }
}edges[N << 1];
int n, m, fa[N];
int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}

int kruskal()
{
    sort(edges, edges + m);
    int res = 0, cnt = 0;
    for(int i = 0; i < m; i ++)
    {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if(find(u) != find(v))
        {
            res += w; cnt ++;
            fa[find(u)] = find(v);
        }
    }
    if(cnt < n - 1) return -1;
    return res;
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i ++)
    {
        int u, v, w;
        cin >> u >> v >> w; edges[i] = {u, v ,w};
    }
    
    for(int i = 1; i <= n; i ++) fa[i] = i;
    int res = kruskal();
    if(res == -1) cout << "impossible";
    else cout << res;
    return 0;
}