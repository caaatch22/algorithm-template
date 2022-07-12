const int N = 1e5 + 10;
int fa[N], n, m, d[N];

int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
// 对于带权并查集，一般的find函数写作：
int find(int x) {
    if(x == fa[x]) return x;
    int rt = find(fa[x]); //这和下面一行顺序很重要
    d[x] += d[fa[x]]; //可以改成d[x] ^= d[fa[x]],根据权值意义的需要修改
    return fa[x] = rt;
}

void init() {
    for (int i = 1; i <= n; i++) fa[i] = i;
}