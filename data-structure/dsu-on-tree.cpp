#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int mod = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> col(n);
    vector<vector<int>> G(n);
    for (int i = 0; i < n; i ++) {
        cin >> col[i];
    }

    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v), G[v].push_back(u);
    }
    vector<int> sz(n), son(n, -1);
    function<void(int, int)> dfsHson = [&](int u, int fa) {
        sz[u] = 1;
        for (auto v : G[u]) {
            if(v == fa) continue;
            dfsHson(v, u);
            sz[u] += sz[v];
            if(son[u] == -1 || sz[son[u]] < sz[v]) {
                son[u] = v;
            }
        }
    };
    dfsHson(0, -1);

    vector<ll> cnt(n + 1), ans(n);
    ll mx = 0, sum = 0;
    function<void(int, int, int, int)> calc = [&](int u, int fa, int val, int Hson) {
        cnt[col[u]] += val;
        if(cnt[col[u]] > mx) {
            mx = cnt[col[u]];
            sum = col[u];
        } else if(cnt[col[u]] == mx) {
            sum += col[u];
        }
        for (auto v:G[u]) {
            if(v == fa || v == Hson) continue;
            calc(v, u, val, Hson);
        }
    };

    function<void(int, int, int)> dfs2 = [&](int u, int fa, bool isCurHSon) {
        for (auto v:G[u]) {
            if(v == fa || v == son[u]) continue;
            dfs2(v, u, 0);
        }
        if(son[u] != -1) {
            dfs2(son[u], u, 1);
        }
        calc(u, fa, 1, son[u]); 
        ans[u] = sum;
        // 以下是消除轻儿子的影响
        if(!isCurHSon) {
            calc(u, fa, -1, -1);
            sum = mx = 0;
        }
    };
    dfs2(0, -1, 0);

    for (int i = 0; i < n; i ++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
    return 0;
}
