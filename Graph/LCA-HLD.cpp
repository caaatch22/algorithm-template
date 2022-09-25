struct Tree {
    vector<int> sz, top, dep, parent, in;
    int cur;
    vector<vector<int>> e;
    Tree(int n) : sz(n), top(n), dep(n), parent(n, -1), e(n), in(n), cur(0) {}
    void addEdge(int u, int v) {
        e[u].push_back(v);
        e[v].push_back(u);
    }
    void init() {
        dfsSz(0);
        dfsHLD(0);
    }
    void dfsSz(int u) {
        if (parent[u] != -1)
            e[u].erase(find(e[u].begin(), e[u].end(), parent[u]));
        sz[u] = 1;
        for (int &v : e[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfsSz(v);
            sz[u] += sz[v];
            if (sz[v] > sz[e[u][0]])
                swap(v, e[u][0]);
        }
    }
    void dfsHLD(int u) {
        in[u] = cur++;
        for (int v : e[u]) {
            if (v == e[u][0]) {
                top[v] = top[u];
            } else {
                top[v] = v;
            }
            dfsHLD(v);
        }
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        if (dep[u] < dep[v]) {
            return u;
        } else {
            return v;
        }
    }
};