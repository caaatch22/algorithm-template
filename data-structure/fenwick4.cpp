//scoiHH的项链
//对询问离线+树状数组
//维护区间上的种类
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, a, b) for (int i = (a); i <= (b); i ++)
using namespace std;

template<typename T>
struct fenwick {
    int n;
    vector<T> c;
    fenwick(int _n) : n(_n), c(n + 1) {}
    void add(int x, T v) {
        for (int i = x; i <= n; i += i & -i)
            c[i] += v;
    }
    T sum(int x) {
        T res{0};
        for (int i = x; i; i -= i & -i) {
            res += c[i];
        }
        return res;
    }
};

struct Query {
    int l, r, id;
    bool operator<(const Query&rhs) const {
        return r == rhs.r ? l < rhs.l : r < rhs.r;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n;
    fenwick<int> fen(n);
    vector<int> a(n + 1);
    rep(i, 1, n) cin >> a[i];
    int mx = *max_element(a.begin(), a.end()) + 1;
    vector<int> last(mx);
    cin >> m;
    vector<Query> qs(m);
    vector<int> ans(m);
    rep(i, 0, m - 1) {
        int l, r;
        cin >> l >> r;
        qs[i] = {l, r, i};
    }
    sort(qs.begin(), qs.end());

    int p = 1;
    rep(i, 0, m - 1) {
        auto [l, r, id] = qs[i];
        rep(j, p, r) {
            if(last[a[j]]) fen.add(last[a[j]], -1);
            fen.add(j, 1);
            last[a[j]] = j;
        }
        p = r + 1;
        ans[id] = fen.sum(r) - fen.sum(l - 1);
    }
    rep(i, 0, m - 1) {
        cout << ans[i] << '\n';
    }
    return 0;
}