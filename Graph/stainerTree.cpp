#include <bits/stdc++.h>

using namespace std;

int n, m, k, dp[1024][101];
vector<pair<int, int>> g[101];
bool vis[101];
void Spfa(int S) {
    queue<int> q;
    for (int i = 0; i < n; i++)
        if (dp[S][i] != 0x3f3f3f3f)
            q.emplace(i), vis[i] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (auto &&[v, w] : g[u])
            if (dp[S][u] + w < dp[S][v]) {
                dp[S][v] = dp[S][u] + w;
                if (!vis[v])
                    q.emplace(v), vis[v] = true;
            }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w, u--, v--;
        g[u].emplace_back(v, w), g[v].emplace_back(u, w); 
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x, x--;
        dp[1 << i][x] = 0;
    }
    for (int S = 1; S < (1 << k); S++) {
        for (int T = S & (S - 1); T; T = (T - 1) & S) {
            if (T < (S ^ T))
                break;
            for (int i = 0; i < n; i++)
                dp[S][i] = min(dp[S][i], dp[T][i] + dp[T ^ S][i]);
        }
        Spfa(S);
    }
  cout << *min_element(dp[(1 << k) - 1], dp[(1 << k) - 1] + n);
  return 0;
}