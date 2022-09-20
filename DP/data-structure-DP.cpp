#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

struct Info {
    int x, y;
    Info(int _x = 0, int _y = 0):x(_x), y(_y) {}
};

Info operator+(const Info& a, const Info& b) {
    if(a.x == b.x) {
        return {a.x, (a.y + b.y) % mod};
    } else {
        if(a.x > b.x) {
            return a;
        } else {
            return b;
        }
    }
}

template<typename T, typename OP = plus<T>>
struct fenwick {
    const int n;
    vector<T> c;
    const OP op;
    fenwick(int _n) : n(_n), c(_n + 1), op(OP()) {}
    void add(int pos, T v) {
        for (int i = pos; i <= n; i += i & -i) {
            c[i] = op(c[i], v);
        }
    }
    T query(int pos) {
        T res;
        for (int i = pos; i; i -= i & -i) {
            res = op(res, c[i]);
        }
        return res;
    }
};


void discrete(vector<int>& a) {
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (size_t i = 0; i < a.size();  i++) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    discrete(a);
    vector<int> f(n, 1), dp(n, 1);

    fenwick<Info> fen(n);

    int ans = 0, LIS = 0;
    for (int i = 0; i < n; i++) {
        // cout << "i = " << i << '\n';
        
        auto t = fen.query(a[i] - 1);
        f[i] = t.x + 1;
        dp[i] = max(1, t.y);
        fen.add(a[i], {f[i], dp[i]});
        LIS = max(f[i], LIS);
    }

    
    for (int i = 0; i < n; i ++) {
        if(f[i] == LIS)
            (ans += dp[i]) %= mod;
    }
    cout << ans << '\n';
    return 0;   
}