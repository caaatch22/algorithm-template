// kruskal
using ll = long long;
struct Edge {
    int u, v, w;
    bool operator<(const edge &rhs) const { return w < rhs.w; }
};

struct DSU {
    int n;
    vector<int> f;
    DSU(int n): n(n), f(n) { iota(f.begin(), f.end(), 0); }
    int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return false;
        f[v] = u;
        return true;
    } 
};

int kruskal() {
    cin >> n >> m;
    ll ans = 0;
    vector<Edge> edge(m);
    for (int i = 0; i < m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edge[i] = {u, v, w};
    }
    sort(edge.begin(), edge.end());
    DSU dsu(n);
    for (auto [u, v, w]: edge) {
        if(dsu.merge(u, v)) {
            ans += w;
        }
    }
    return ans;
}


//prim
const int N = 510, inf = 0x3f3f3f3f;
int G[N][N], dis[N];
int n, m;
bool vis[N];

int prim() {
    int res = 0;
    memset(dis, 0x3f, sizeof dis);
    dis[1] = 0;   //随便选一点进入mst集合
    for(int j = 0; j < n; j ++) {
        int minv = inf, pos = -1;
        for(int i = 1; i <= n; i ++)
            if(!vis[i] && dis[i] < minv)
                pos = i, minv = dis[i];
                
        if(pos == -1) return inf;
        vis[pos] = true;
        res += dis[pos];
        
        for(int i = 1; i <= n; i ++)
            if(!vis[i] && dis[i] > G[pos][i])
                dis[i] = G[pos][i];
    }
    return res;
}