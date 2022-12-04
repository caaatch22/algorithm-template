// https://codeforces.com/problemset/problem/600/E
// 树的节点有颜色，我们称一种颜色占领了一个子树，
// 当且仅当没有其他颜色在这个子树中出现得比它多。
// 求占领每个子树的所有颜色之和。

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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
    vector<int> sz(n), son(n, -1); // son[u]表示u的重儿子
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

    function<void(int, int, int)> dfs = [&](int u, int fa, bool isCurHSon) {
        for (auto v:G[u]) {
            if(v == fa || v == son[u]) continue;
            dfs(v, u, false);
        }
        if(son[u] != -1) {
            dfs(son[u], u, true);
        }
        calc(u, fa, 1, son[u]); 
        ans[u] = sum;

        // 如果当前点是其父节点的轻儿子，则消除其影响
        if(!isCurHSon) {
            calc(u, fa, -1, -1);
            sum = mx = 0;
        }
    };
    dfs(0, -1, false);

    for (int i = 0; i < n; i ++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
    return 0;
}
