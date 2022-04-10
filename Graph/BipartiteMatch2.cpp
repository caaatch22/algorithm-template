#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 10000 + 10;
int n, t, dx[] = {-1, 0, 0, 1}, dy[] = {0, 1, -1, 0};
vector<int> G[N];
int w[N], p[N];
bool vis[N];

bool match(int u) {
    for(auto v:G[u]) {
        if(!vis[v]) {
            vis[v] = true;
            if(p[v] == 0 || match(p[v])) {
                p[v] = u;
                return true;
            }
        }
    }
    return false;
}

int get_id(int x, int y) {return (x - 1)* n + y;}

int main() {
    cin >> n >> t;
    while(t -- ) {
        int x, y;
        cin >> x >> y;
        w[get_id(x, y)] = 1;
    }
    
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= n; j ++) {
            int id = get_id(i, j);
            if(w[id]) continue;
            for(int k = 0; k < 4; k ++) {
                int x = i + dx[k], y = j + dy[k];
                if(x < 1 || y < 1 || x > n || y > n) continue;
                int id2 = get_id(x, y);
                //cout << id2 << endl;
                if(!w[id2])    G[id].pb(id2);
            }
        }
    }
    
    int res = 0;
    for(int i = 1; i <= n * n; ++i) {
        memset(vis, 0, sizeof(vis));
        if(match(i)) res ++;
    }
    cout << res / 2;
    
    return 0;
}

/*dinic解二分图
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

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
        for(auto [v, cap, rev] : G[u]) {
            if(dep[v] == -1 && cap) {
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }
    return dep[t] != -1;
}

ll dfs(int u, ll lim) {
    if(u == t || lim == 0) return lim;
    ll tot_flow = 0;
    for(auto& [v, cap, rev] : G[u]) {
        if(dep[v] == dep[u] + 1 && cap > 0) {
            ll d = dfs(v, min(lim, (ll)cap));
            cap -= d;
            G[v][rev].cap += d;
            lim -= d;
            tot_flow += d;
            if(lim == 0)  return tot_flow;
        } 
    }
    if(lim != 0) dep[u] = -1;
    return tot_flow;
}

ll dinic() {
    ll res = 0;
    while(bfs())
        res += dfs(s, inf);
    return res;
}

void add(int u, int v, int cap) {
    G[u].pb({v, cap, G[v].size()});
    G[v].pb({u, 0, G[u].size() - 1});
}

int main() {
    scanf("%d%d", &m, &n);
    s = 0, t = n + 1;
    
    for (int i = 1; i <= m; i ++ ) add(s, i, 1);
    for (int i = m + 1; i <= n; i ++ ) add(i, t, 1);

    int a, b;
    while (cin >> a >> b, a != -1) add(a, b, 1);

    printf("%d\n", dinic());

    for(int i = 1; i <= m; i ++) 
        for(auto [v, cap, rev] : G[i])
            if(cap == 0 && v >= m + 1)
                printf("%d %d\n", i, v);

    return 0;
}
*/