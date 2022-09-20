/*
求lca： 1.倍增  2.树剖  3.tarjan离线
lca用处
1. 树上两点之间的距离 （多维护一个dist数组， dis[u] + dis[v] - 2 * dis[lca(u, v)]）
2. 树上两条路径是否相交 （如果两条路径相交，那么一定有一条路径的LCA在另一条路径上）
*/
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 1e4 + 10;

struct node{int v, w;};
vector<node> G[N];
int fa[N][19], dep[N], dis[N];
int n, m;

void bfs(int s) {
    memset(dep, 0x3f, sizeof dep);
    dep[0] = 0, dep[s] = 1;
    dis[s] = 0;
    queue<int> q; q.push(s);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(auto [v, w] : G[u]) {
            if(dep[v] > dep[u] + 1) {
                dis[v] = dis[u] + w;
                dep[v] = dep[u] + 1;
                fa[v][0] = u;
                q.push(v);
                for(int i = 1; i < 19; ++i)
                    fa[v][i] = fa[fa[v][i - 1]][i - 1];
            }
        }
    }
}

int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for(int k = 18; k >= 0; k--)
        if(dep[fa[a][k]] >= dep[b])
            a = fa[a][k];
    if(a == b) return a;
    
    for(int k = 18; k >= 0; --k)
        if(fa[a][k] != fa[b][k])
            a = fa[a][k], b = fa[b][k];
    return fa[a][0];
}
