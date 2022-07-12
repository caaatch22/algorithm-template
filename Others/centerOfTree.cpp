// acwing846
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 1e5 + 10;
vector<int> G[N];
int n, sz[N];
bool vis[N];
int res = 0x3f3f3f3f;

void dfs(int u) {
    vis[u] = true; sz[u] = 1;
    int max_part = 0;
    for(auto v : G[u]) {
        if(vis[v]) continue;
        dfs(v);
        sz[u] += sz[v];
        max_part = max(max_part, sz[v]);
    }
    max_part = max(n - sz[u], max_part);
    res = min(res, max_part);
}


int main() {
    scanf("%d", &n);
    for(int i = 1; i < n; i ++) {
        int u, v;  scanf("%d %d", &u, &v);
        G[u].pb(v), G[v].pb(u);
    }
    
    dfs(1);
    cout << res;
    return 0;
}