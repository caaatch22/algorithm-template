//静态二维数点
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++)
using namespace std;
using ll = long long;

struct fenwick {
    int n;
    vector<ll> c;
    fenwick(int _n) : n(_n), c(_n + 1, 0) {}
    void add(int x, ll v) {
        for (int i = x; i <= n; i += i&-i) {
            c[i] += v;
        }
    }
    ll sum(int x) {
        ll res = 0;
        for (int i = x; i; i -= i&-i) {
            res += c[i];
        }
        return res;
    }
};

struct query {
    int x, y;
    int id, sgn;
    bool operator<(const query&rhs) const {
        return x < rhs.x;
    }
};

void solve() {
    int n, m, mx = 0;
    cin >> n >> m;
    vector<pair<int, int>> ord(n);
    for (auto &[x, y]:ord) {
        cin >> x >> y;
        x++, y++;
        mx = max(mx, y);
    }
    sort(ord.begin(), ord.end());
    vector<query> q(4 * m);
    int cnt = 0;
    rep(i, 0, m - 1) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a++, b++, c++, d++;
        q[cnt++] = {c, d, i, 1};
        q[cnt++] = {a - 1, d, i, -1};
        q[cnt++] = {c, b - 1, i, -1};
        q[cnt++] = {a - 1, b - 1, i, 1};
        mx = max({mx, a, b, c, d});
    }
    sort(q.begin(), q.end());
    vector<ll> ans(m, 0);
    //cout << "mx = " << mx << '\n';
    fenwick fen(mx);
    int last = 0;
    for (int i = 0; i < 4 * m; i ++) {
        auto [x, y, id, sgn] = q[i];
        
        while(last < n && ord[last].first <= x) {
            fen.add(ord[last].second, 1);
            last++;
        }
        auto t = fen.sum(y);
        ans[id] += t * sgn;
    }

    for (auto i:ans) {
        cout << i << '\n';
    }
}   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1; // cin >> T;
    while(T --) {
        solve();
    }
    return 0;
}

