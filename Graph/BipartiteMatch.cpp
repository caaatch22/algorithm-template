/* 染色法判断二分图
bool vis[N];
int col[N], flag = 1, n, m;
void dfs(int u, int t) {
    if (vis[u]) {
        if (col[u] != t) flag = 0;
        return;
    }
    vis[u] = 1; col[u] = t;
    for (int v : g[u]) {
        dfs(v, t ^ 1);
    }
}
bool isbit() {//是否为二分图
    for (int u = 1; u <= n; u++) {
        if (!vis[u]) dfs(u, 0);
    }
    return flag;
}
*/
int G[N][M];  // 左半部n, 右半部m
int n, m, p[M], vis[M];
bool match(int u) {
    for (int i = 1; i <= m; i ++) {
        if(G[u][i] && !vis[i]) {
            vis[i] = true;
            if(p[i] == 0 || match(p[i])) {
                p[i] = u;  return true;
            }
        }
    }
    return false;
}
int main() {
    /*建图*/
    int res = 0;
    for (int i = 1; i <= n; i ++) {
        memset(vis, 0, sizeof vis);
        if(match(i)) res++;
    }
    return 0;
}