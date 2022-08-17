#include <bits/stdc++.h>
using namespace std;

class SuffixArray {
//得到的sa[]，rk[]下标从0开始，ht下标从1开始（因为是长度）
private:
    int n, m;
    vector<int> x, y, cnt;
    void radixSort() {
        for (int i = 0; i < m; ++ i) cnt[i] = 0;
        for (int i = 0; i < n; ++ i) cnt[x[i]] ++;
        for (int i = 1; i < m; ++ i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; -- i) sa[-- cnt[x[y[i]]]] = y[i];
    }
public:
    vector<int> sa, rk, ht;

    SuffixArray(const string &s) : 
        n(s.size()), m(256), //m为字符集最大数量
        x(n), y(n), cnt(max(n, m)),
        sa(n), rk(n), ht(n) {
        init_sa(s);
        init_ht(s);
    }
    void init_sa(const string &s) {
        for (int i = 0; i < n; ++ i) {
            x[i] = s[i];
            y[i] = i;
        }
        radixSort();
        for (int w = 1; w <= n; w <<= 1) {
            int p = 0;
            for (int i = n - w; i < n; ++ i) y[p ++] = i;
            for (int i = 0; i < n; ++ i) 
                if (sa[i] >= w) y[p ++] = sa[i] - w;

            radixSort();
            swap(x, y);
            x[sa[0]] = 0;
            p = 1;
            auto cmp = [&](int i, int j) {
                if (i < n && j < n) return y[i] == y[j];
                return i >= n && j >= n;
            };
            for (int i = 1; i < n; ++ i) 
                x[sa[i]] = (cmp(sa[i], sa[i - 1]) && cmp(sa[i - 1] + w, sa[i] + w)) 
                ? p - 1 : p++;

            if (p >= n) break;
            m = p;
        }
        for (int i = 0; i < n; ++ i) rk[sa[i]] = i;
    }
    void init_ht(const string &s) {
        for (int i = 0, k = 0; i < n; ++ i) {
            if (rk[i] == 0) continue ;
            if (k) k --;
            int j = sa[rk[i] - 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k ++;
            ht[rk[i]] = k;
        }
    }
};

void solve() {
    string s;
    cin >> s;
    SuffixArray f(s);
    for (int i = 0; i < s.size(); ++ i) 
        cout << f.sa[i] + 1 << " \n"[i + 1 == s.size()];
    for (int i = 0; i < s.size(); ++ i) 
        cout << f.ht[i] << " \n"[i + 1 == s.size()];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T -- ) {
        solve();
    }
    return 0;
}