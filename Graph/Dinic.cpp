#include <bits/stdc++.h>
#define pb push_back
using namespace std;
using ll = long long;
const int N = 1e4 + 10;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int n, m, s, t, dep[N];
struct node {int v, cap, rec;};
vector<node> G[N];

bool bfs() {
    queue<int> q;
    q.push(s);
    memset(dep, -1, sizeof dep);
    dep[s] = 0;
    while (q.size()) {
        int u = q.front(); q.pop();
        for(auto [v, cap, rev] : G[u]) 
            if(dep[v] == -1 && cap) 
                dep[v] = dep[u] + 1, q.push(v);
    }
    return dep[t] != -1;
}

ll dfs(int u, ll lim) {
    if(u == t || lim == 0) return lim;
    ll tot_flow = 0;
    for(auto& [v, cap, rev] : G[u]) {
        if(dep[v] == dep[u] + 1 && cap > 0) {
            ll d = dfs(v, min(lim, (ll)cap));
            cap -= d, G[v][rev].cap += d;
            lim -= d, tot_flow += d;
            if(lim == 0)  return tot_flow;
        } 
    }
    if(lim != 0) dep[u] = -1;
    return tot_flow;
}

ll dinic() {
    ll max_flow = 0;
    while(bfs())
        max_flow += dfs(s, inf);
    return max_flow;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    while(m --) {
        int u, v, cap;  scanf("%d%d%d", &u, &v, &cap);
        G[u].pb({v, cap, G[v].size()});
        G[v].pb({u, 0, G[u].size() - 1});
    }

    printf("%lld\n", dinic());
    return 0;
}