#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 2e4 + 10;
vector<int> G[N], cut;
int tim, n, m, root;
int dfn[N], low[N];

void tarjan(int u) {
    low[u] = dfn[u] = ++tim;
    int tot = 0;
    for(int v:G[u]) {
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v])
                tot++;
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
    if ( (tot > 0 && u != root) || (tot > 1 && u == root))
        cut.pb(u);

}

int main() {
    cin >> n >> m;
    while(m --) {
        int u, v;
        cin >> u >> v;
        G[u].pb(v), G[v].pb(u);
    }

    for (root = 1; root <= n; root ++)
        if(!dfn[root])
            tarjan(root);

    //不用sort， 就开一个bool cut[N];
    sort(cut.begin(), cut.end());
    printf("%d\n", cut.size());
    for(int v : cut)
        printf("%d ", v);
    
    return 0;
}