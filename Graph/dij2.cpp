#include <bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;

using P = pair<int, int>;
const int N = 151000, inf = 0x3f3f3f3f;
struct node{int v, w;};
vector<node> G[N];
int dis[N], n, m;
bool vis[N];

void dij() {
    memset(dis, 0x3f, sizeof dis);
    priority_queue<P, vector<P>, greater<P>> q;
    q.push({0, 1});
    while(q.size()) {
        auto t = q.top(); q.pop();
        int u = t.se, d = t.fi;
        if(vis[u]) continue;
        vis[u] = true;
        for(auto [v, w] : G[u]) {
            if(dis[v] > d + w) {
                dis[v] = d + w;
                q.push({dis[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    while(m -- ) {
        int u, v, w; cin >> u >> v >> w;
        G[u].pb({v, w});
    }
    dij();
    cout << (dis[n] == inf ? -1 : dis[n]);   
    return 0;
}