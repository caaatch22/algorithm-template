// 一个有桥的连通图,如何把它通过加边变成边双连通图?
// 1. 求出所有的桥,然后删除这些桥边, 剩下的每个连通块都是一个双连通子图。
// 把每个双连通子图收缩为一个顶点 ,再把桥边加回来,最后的这图一定是一棵树,边连通度为 1。
// 2 统计出树中度为 1 的节点的个数,即为叶节点的个数,记为 cnt。
// 3. 则至少在树上添加(cnt+1)/2 条边,就能 使树达到边二连通,所以至少添加的边数就是(cnt+1)/2。
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 5010;
int n, m;
vector<int> G[N];
int low[N], dfn[N], id[N], deg[N];
int dcc_cnt, tim, stk[N], top;
vector<int> bridge[N];

void tarjan(int u, int fa) {
    low[u] = dfn[u] = ++tim;
    stk[++top] = u;

    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[v], low[u]);
            if(dfn[u] < low[v])
                bridge[u].pb(v), bridge[v].pb(u);
        }
        else if(fa != v)
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        int y;
        ++dcc_cnt;
        do {
            y = stk[top--];
            id[y] = dcc_cnt;
        } while (u != y);
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m;
    while(m -- ) {
        int u, v;
        cin >> u >> v;
        G[u].pb(v), G[v].pb(u);
    }
    tarjan(1, -1);
    for (int u = 1; u <= n; u++)
        deg[id[u]] += bridge[u].size();
    int cnt = 0;
    for (int i = 1; i <= dcc_cnt; i ++)
        if(deg[i] == 1)
            cnt++;
    cout << (cnt + 1) / 2;
    return 0;
}