struct DSU {
    vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    // int find(int x) { // 带权并查集
    //     if(x == f[x]) return x;
    //     int rt = find(f[x]); //这和下面一行顺序很重要
    //     d[x] += d[f[x]]; //可以改成d[x] ^= d[fa[x]], 根据权值意义的需要修改
    //     return f[x] = rt;
    // }
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};