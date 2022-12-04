// https://ac.nowcoder.com/acm/contest/31084/E
// 维护dfs序从而在calc时减小常熟的方法（非递归完成计算）
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 1e5;

vector<int> divisors[N];
void init() {
    // time complexity N \sqrt{N} =>  N < 1e5
    for (int i = 1; i <= N; i ++) {
        for (int j = 1; j <= i / j; j ++) {
            if(i % j == 0) {
                divisors[i].push_back(j);
                if(j * j != i) { // j*j一定不会爆int, 因为时间复杂度为 nsqrt(n)
                    divisors[i].push_back(i / j);
                }
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> G(n);
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<int> a(n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }

    vector<int> l(n), r(n), seq(n);
    int tim = 0;
    vector<int> sz(n), son(n, -1);
    function<void(int, int)> dfsHson = [&](int u, int fa) {
        sz[u] = 1;
        seq[tim] = u;
        l[u] = tim++;
        for (auto v: G[u]) {
            if(v == fa) continue;
            dfsHson(v, u);
            sz[u] += sz[v];
            if(son[u] == -1 || sz[son[u]] < sz[v]) {
                son[u] = v;
            }
        }
        r[u] = tim - 1;
    };
    dfsHson(0, -1);

    // for (int i = 0; i < n; i ++) {
    //     cerr << "son[" << i << "] = " << son[i] << " \n"[i == n - 1];
    // }
    // for (int i = 0; i < n; i ++) {
    //     cerr << "l[" << i << "]=" << l[i] << " \n"[i == n - 1];
    // }
    // for (int i = 0; i < n; i ++) {
    //     cerr << "r[" << i << "]=" << r[i] << " \n"[i == n - 1];
    // }

    vector<int> buc(N + 1);
    vector<pair<int, int>> ans(n);
    int mx = 0, cnt = 0;
    auto updateBuc = [&](int u, int t) {
        for (auto d: divisors[a[u]]) {
            buc[d] += t;
        }
    };
    auto updateAns = [&](int u) {
        for (auto d: divisors[a[u]]) {
            if(buc[d]) {
                if(d > mx) mx = d, cnt = buc[d];
                else if(d == mx) cnt += buc[d];
            }
        }
    };

    function<void(int, int, bool)> dfs = [&](int u, int fa, bool isCurHson) {
        for (auto v: G[u]) {
            if(v == fa || v == son[u])  continue;
            dfs(v, u, false);
        }
        if(son[u] != -1) {
            dfs(son[u], u, true);
        }
        mx = cnt = 0;
        for (auto v: G[u]) {
            if(v == fa || v == son[u]) continue;
            for (int p = l[v]; p <= r[v]; p ++) {
                updateAns(seq[p]);
            }
            for (int p = l[v]; p <= r[v]; p ++) {
                updateBuc(seq[p], 1);
            }
        }
        updateAns(u);
        updateBuc(u, 1);
        ans[u] = {mx, cnt};
        if(!isCurHson) {
            for (int p = l[u]; p <= r[u]; p ++) {
                updateBuc(seq[p], -1);
            }
        }

    };
    dfs(0, -1, false);

    for (auto [x, y]: ans) {
        cout << x << ' ' << y << '\n';
    }
        
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1; // cin >> T;
    init();
    while(T --) {
        solve();
    }
    
    return 0;
}