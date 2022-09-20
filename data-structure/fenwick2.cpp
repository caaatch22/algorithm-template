//区间覆盖一个新的种类（不会掩盖已有属性）
//询问区间总共有多少属性
//luogu2184  差分思想
#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct fenwick {
    int n;
    vector<T> c;
    fenwick(int _n) : n(_n), c(n + 1, 0) {}
    void add(int x, T v) {
        for (int i = x; i <= n; i += i & -i) {
            c[i] += v;
        }
    }
    T sum(int x) {
        T res{0};
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
    fenwick<int> t1(n), t2(n);

    while(m --) {
        int op, l, r;
        cin >> op >> l >> r;
        if(op == 1)  t1.add(l, 1), t2.add(r, 1);
        else
            cout << t1.sum(r) - t2.sum(l - 1) << '\n';
    }
    return 0;
}