//kruskal重构树

//性质：
//两个点之间的所有简单路径上最大边权的最小值 
//  = 最小生成树上两个点之间的简单路径上的最大值 
//  = Kruskal 重构树上两点之间的 LCA 的权值。
//loj136
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 1010 << 1, M = 3e5 + 10;
int n, m, k, val[N];// kruskal重构树的点权
int idx;  //重构树的节点数

struct Edge{
    int u, v, w;
    bool operator<(const Edge &rhs) const { return w < rhs.w; }
}edges[M];

vector<int> G[N];

int p[N];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }

int dep[N], fa[N][21];

void bfs(int s) {
    dep[0] = 0, dep[s] = 1;
    queue<int> q;
    q.push(s);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int v:G[u]) {
            if(dep[v] > dep[u] + 1) {
                dep[v] = dep[u] + 1;
                q.push(v);
                fa[v][0] = u;
                for (int i = 1; i <= 20; i ++)
                    fa[v][i] = fa[fa[v][i - 1]][i - 1];
            }
        }
    }
}

int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for (int k = 20; k >= 0; k --)
        if(dep[fa[a][k]] >= dep[b])
            a = fa[a][k];
    if(a == b) return a;
    for (int k = 20; k >= 0; k --)
        if(fa[a][k] != fa[b][k])
            a = fa[a][k], b = fa[b][k];
    return fa[a][0];
}

void build() {
    idx = n;
    int cnt = 0;
    for (int i = 1; i <= m; i ++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        int fu = find(u), fv = find(v);
        if(fu != fv) {
            val[++idx] = w;
            G[idx].pb(fu), G[idx].pb(fv);
            G[fu].pb(idx), G[fv].pb(idx);
            p[fu] = p[fv] = idx;
            cnt++;
        }
        if(cnt >= n - 1) break;
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= m; i ++) {
        int u, v, w;  scanf("%d %d %d", &u, &v, &w);
        edges[i] = {u, v, w};
    }
    sort(edges + 1, edges + m + 1);
    for (int i = 1; i <= (n << 1); i ++)  p[i] = i;
    
    build(); // kruskal重构树

    memset(dep, 0x3f, sizeof dep);
    bfs(idx);  //bfs的根节点一定要是重构树的最高点

    while(k -- ) {
        int s, t;
        scanf("%d %d", &s, &t);
        if(find(s) != find(t))    puts("-1");
        else
            printf("%d\n", val[lca(s, t)]);
    }
    return 0;
}