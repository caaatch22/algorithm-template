// fenwich-tree写区间修改，区间查询
//记录两个数组 b[i] = a[i] - a[i - 1]; c[i] = i * b[i];
// a[1~x] = \sum_{i=1}{x} \sum_{j=1}{i}b[j]
// = \sum{i=1}{x}(x-i+1)*b[i] 
// = (x+1)\sum_{i=1}{x}b[i] - \sum_{i=1}{x}i*b[i]

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++)
using namespace std;
using ll = long long;

template<typename T/*, class OP = plus<T>*/>
struct fenwick {
    int n;
    // const OP op;
    vector<T> c;
    fenwick(int _n) : n(_n), c(_n + 1, 0)/*, op(OP())*/ {}
    void add(int x, T v) {
        for (int i = x; i <= n; i += i & -i) {
            c[i] += v; // c[i] = op(c[i], v)
        }
    }
    T sum(int x) {
        T res{};
        for (int i = x; i; i -= i & -i) {
            res += c[i];
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    fenwick<ll> t1(n), t2(n); //维护b[i], b[i] * i的前缀和
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) {
        int b = a[i] - a[i - 1];
        t1.add(i, b);
        t2.add(i, 1ll * b * i);
    }
    auto preSum = [&](int x) {
        return t1.sum(x)*(x + 1) - t2.sum(x);
    };
    while(m --) {
        int op, l, r, d;
        cin >> op >> l >> r;
        if(op == 2) {
            cout << preSum(r) - preSum(l - 1) << '\n';
        }
        else {
            cin >> d;
            t1.add(l, d);
            t2.add(l, 1ll* l * d);
            t1.add(r + 1, -d);
            t2.add(r + 1, 1ll * (r + 1) * -d);
        }
    }
    return 0;
}