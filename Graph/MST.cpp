// kruskal
const int N = 1e5 + 10;
struct edge {
    int u, v, w;
    bool operator<(const edge &rhs) const { return w < rhs.w; }
} edges[N];

int fa[N], n, m;
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int kruskal() {
    cin >> n >> m;
    int u, v, w, ans = 0;
    for (int i = 1; i <= m; i ++) {
        cin >> u >> v >> w;
        edges[i] = {u, v, w};   
    }
    sort(edges + 1, edges + 1 + m);
    for (int i = 1; i <= n; i ++) fa[i] = i;
    for (int i = 1; i <= m; i ++) {
        auto [u, v, w] = edges[i];
        u = find(u), v = find(v);
        if(u == v) continue;
        fa[u] = v;
        ans += w;
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