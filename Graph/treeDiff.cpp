//jloi2014松鼠的新家 树上差分
//树剖也可以做
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 3e5 + 10;
int n, a[N], fa[N][23], dep[N], diff[N];

vector<int> G[N];

void dfs(int u, int fath) {
    dep[u] = dep[fath] + 1, fa[u][0] = fath;
    for (int i = 1; i <= 22; i ++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];

    for(int v:G[u]) {
        if(v == fath) continue;
        dfs(v, u);
    }
}

int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for (int k = 22; k >= 0; k --)
        if(dep[fa[a][k]] >= dep[b])
            a = fa[a][k];
    if(a == b)  return a;
    for (int k = 22; k >= 0; k --)
        if(fa[a][k] != fa[b][k])
            a = fa[a][k], b = fa[b][k];
    return fa[a][0];
}
//树上的差分数组求和的时候
void sumup(int u, int fath) {
    for(int v:G[u]) {
        if(v == fath) continue;
        sumup(v, u);
        diff[u] += diff[v];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);

    for (int i = 1; i < n; i ++) {
        int u, v;  scanf("%d%d", &u, &v);
        G[u].pb(v), G[v].pb(u);
    }

    dfs(1, 0);
    for (int i = 1; i < n; i ++) {
        int u = a[i], v = a[i + 1];
        int anc = lca(u, v);
        diff[fa[anc][0]]--;
        diff[u]++, diff[v]++;
        diff[anc]--;
    }

    sumup(1, 0);
    for (int i = 2; i <= n; i ++)   diff[a[i]]--;

    for (int i = 1; i <= n; i ++)
        printf("%d\n", diff[i]);

    return 0;
}