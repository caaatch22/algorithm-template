// 树状数组解法
// #include <bits/stdc++.h>
// #define rep(i, a, b) for (int i = (a); i <= (b); i ++)
// using namespace std;
// using ll = long long;

// struct fenwick {
//     int n;
//     vector<ll> c;
//     fenwick(int _n) : n(_n), c(_n + 1, 0) {}
//     void add(int x, ll v) {
//         for (int i = x; i <= n; i += i&-i) {
//             c[i] += v;
//         }
//     }
//     ll sum(int x) {
//         ll res = 0;
//         for (int i = x; i; i -= i&-i) {
//             res += c[i];
//         }
//         return res;
//     }
// };

// struct query {
//     int x, y;
//     int id, sgn;
//     bool operator<(const query&rhs) const {
//         return x < rhs.x;
//     }
// };

// void solve() {
//     int n, m, mx = 0;
//     cin >> n >> m;
//     vector<pair<int, int>> ord(n);
//     for (auto &[x, y]:ord) {
//         cin >> x >> y;
//         x++, y++;
//         mx = max(mx, y);
//     }
//     sort(ord.begin(), ord.end());
//     vector<query> q(4 * m);
//     int cnt = 0;
//     rep(i, 0, m - 1) {
//         int a, b, c, d;
//         cin >> a >> b >> c >> d;
//         a++, b++, c++, d++;
//         q[cnt++] = {c, d, i, 1};
//         q[cnt++] = {a - 1, d, i, -1};
//         q[cnt++] = {c, b - 1, i, -1};
//         q[cnt++] = {a - 1, b - 1, i, 1};
//         mx = max({mx, a, b, c, d});
//     }
//     sort(q.begin(), q.end());
//     vector<ll> ans(m, 0);
//     //cout << "mx = " << mx << '\n';
//     fenwick fen(mx);
//     int last = 0;
//     for (int i = 0; i < 4 * m; i ++) {
//         auto [x, y, id, sgn] = q[i];
        
//         while(last < n && ord[last].first <= x) {
//             fen.add(ord[last].second, 1);
//             last++;
//         }
//         auto t = fen.sum(y);
//         ans[id] += t * sgn;
//     }

//     for (auto i:ans) {
//         cout << i << '\n';
//     }
// }   

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int T = 1; // cin >> T;
//     while(T --) {
//         solve();
//     }
//     return 0;
// }


// 静态二维数点的cdq解法
// 将初始点看成修改操作，有修改查询
#include <bits/stdc++.h>
using ll = long long;
using namespace std;
struct Node {
    // {坐标} 
    int x, y, sgn, id;
    bool operator<(const Node&rhs) const {
        if(x == rhs.x) {
            if(y == rhs.y) {
                if(sgn == 0) {
                    return 1;
                } else if(rhs.sgn == 0) {
                    return 0;
                }
            } else {
                return y < rhs.y;
            }
        } else {
            return x < rhs.x;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int cnt = 0;
    vector<Node> node(n + 4 * m);
    for (int i = 0; i < n; i ++) {
        int x, y;
        cin >> x >> y;
        node[cnt++] = {x, y, 0, 0};
    }
    for (int i = 0; i < m; i ++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        node[cnt++] = {a - 1, b - 1, 1, i};
        node[cnt++] = {c, d, 1, i};
        node[cnt++] = {a - 1, d, -1, i};
        node[cnt++] = {c, b - 1, -1, i};
    }
    sort(node.begin(), node.end());
    // for (int i = 0; i < cnt; i ++) {
    //     cout << node[i].sgn << ' ';
    //     cout << node[i].x << ' ' << node[i].y << '\n';
    // }
    // cout << "\n";

    vector<ll> ans(m, 0);
    vector<Node> tmp(4 * m + n);

    function<void(int, int)> cdq = [&](int l, int r) {
        if(r - l <= 1) {
            return;
        }
        int m = (l + r) / 2;
        cdq(l, m); cdq(m, r);
        // static array<Node, 4 * m + n> tmp{};
        int i = m, j = l, idx = 0;
        ll sum = 0;
        while(i < r && j < m) {
            if(node[j].y <= node[i].y) {
                if(node[j].sgn == 0)  ++sum;
                tmp[idx++] = node[j++];
            } else {
                ans[node[i].id] += node[i].sgn * sum;
                tmp[idx++] = node[i++];
            }
        }
        while(j < m) {
            tmp[idx++] = node[j++];
        }
        while(i < r) {
            ans[node[i].id] += node[i].sgn * sum;
            tmp[idx++] = node[i++];
        }
        assert((r - l) >= idx);
        copy(tmp.begin(), tmp.begin() + idx, node.begin() + l);
    };
    assert(cnt == n + 4 * m);
    cdq(0, n + 4 * m);
    for (int i = 0; i < m; i ++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
