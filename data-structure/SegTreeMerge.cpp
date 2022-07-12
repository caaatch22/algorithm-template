//luogu 4556
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 1e5 + 10;
int fa[N][19], dep[N], n, m;
vector<int> G[N];
using P = pair<int, int>;
struct node {
    int l, r;
    P val;   //救济粮的数量，种类
} t[N * 75];
int cnt, rt[N], idx, ans[N];

P& max(P& x, P& y) {
    if(x.first > y.first) return x;
    else if(x.first == y.first) return x.second < y.second ? x : y;
    else return y;
}


int insert(int now, int l, int r, int x, int val) {
    //if(!p) p = ++idx;
    int p = ++idx;
    t[p] = t[now];
    if(l == r) {
        t[p].val.first += val;
        t[p].val.second = x;   //救济粮的种类
        return p;
    }
    int mid = l + r >> 1;
    if(x <= mid) t[p].l = insert(t[now].l, l, mid, x, val);
    else t[p].r = insert(t[now].r, mid + 1, r, x, val);
    t[p].val = max(t[t[p].l].val, t[t[p].r].val);
    return p;
}

int merge(int p, int q, int l, int r) {
    if(!p) return q;
    if(!q) return p;
    if(l == r) {
        t[p].val.first += t[q].val.first;
        //t[p].val.second = l;
        return p;
    }
    int mid = l + r >> 1;
    t[p].l = merge(t[p].l, t[q].l, l, mid);
    t[p].r = merge(t[p].r, t[q].r, mid + 1, r);
    t[p].val = max(t[t[p].l].val, t[t[p].r].val);
    return p;
}

void bfs() {
    dep[0] = 0, dep[1] = 1;
    queue<int> q;
    q.push(1);
    while(q.size()) {
        int u = q.front(); q.pop();
        for (auto v:G[u]) {
            if(dep[v]) continue;
            dep[v] = dep[u] + 1;
            q.push(v);
            fa[v][0] = u;
            for (int i = 1; i <= 18; i ++)
                fa[v][i] = fa[fa[v][i - 1]][i - 1];
        }
    }
}

int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for (int k = 18; k >= 0; k --)
        if(dep[fa[a][k]] >= dep[b])
            a = fa[a][k];
    if(a == b) return a;
    for (int k = 18; k >= 0; k --) 
        if(fa[a][k] != fa[b][k])
            a = fa[a][k], b = fa[b][k];
    return fa[a][0];
}

void dfs(int u, int fath) {
    for (auto v:G[u]) {
        if(v == fath) continue;
        dfs(v, u);
        rt[u] = merge(rt[u], rt[v], 1, N);
    }
    if(t[rt[u]].val.first)  ans[u] = t[rt[u]].val.second;
    
}

int main() {

    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i ++) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].pb(v), G[v].pb(u);
    }
    bfs();
    while(m -- ) {
        int u, v, z;
        scanf("%d%d%d", &u, &v, &z);
        rt[u] = insert(rt[u], 1, N, z, 1);
        rt[v] = insert(rt[v], 1, N, z, 1);
        int anc = lca(u, v);
        // printf("lca(%d,%d) = %d\n", u, v, anc);
        // printf("fa[%d][0] = %d\n", anc, fa[anc][0]);
        rt[anc] = insert(rt[anc], 1, N, z, -1);
        rt[fa[anc][0]] = insert(rt[fa[anc][0]], 1, N, z, -1);
    }
    
    dfs(1, 0);
    for (int i = 1; i <= n; i ++)
        printf("%d\n", ans[i]);
    return 0;
}