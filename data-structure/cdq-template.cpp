// 三维偏序模板
#include <bits/stdc++.h>

using namespace std;

struct Node {
    int x, y, z, cnt, ans; // cnt： 坐标都为{x, y, z}的点数量
    bool operator<(const Node&rhs) const {
        if(x != rhs.x) return x < rhs.x;
        if(y != rhs.y) return y < rhs.y;
        return z < rhs.z;
    }
};

struct fenwick {
    const int n;
    vector<int> c;
    fenwick(int n) : n(n), c(n + 1) {}
    void add(int pos, int val) {
        for (int i = pos; i <= n; i+= i & -i) {
            c[i] += val;
        }
    }
    int sum(int pos) {
        int res{0};
        for (int i = pos; i; i -= i & -i) {
            res += c[i];
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    map<array<int, 3>, int> s;
    fenwick fen(k);
    for (int i = 0; i < n; i ++) {
        int x, y, z;
        cin >> x >> y >> z;
        s[{x, y, z}]++;
    }
    vector<Node> node(s.size());
    int m = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        auto [x, y, z] = it->first;
        auto cnt = it->second;
        node[m++] = {x, y, z, cnt, 0};
    }
    assert(m == (int)s.size());
    sort(node.begin(), node.end());
    // for (int i = 0; i < m; i ++) {
    //     auto [x, y, z, cnt, _] = node[i];
    //     cout << "x = " << x << ' ' << y << ' ' << z << ' ' << cnt << '\n';
    // }
        
    auto cmp2nd = [&](const Node &lhs, const Node &rhs) -> bool {
        if(lhs.y != rhs.y) return lhs.y < rhs.y;
        return lhs.z < rhs.z;
    };

    function<void(int, int)> cdq = [&](int l, int r) {
        if(r - l == 1) {
            return;
        }
        int m = (l + r) / 2;
        cdq(l, m); cdq(m, r);
        sort(node.begin() + l, node.begin() + m, cmp2nd);
        sort(node.begin() + m, node.begin() + r, cmp2nd);

        int j = l;
        for (int i = m; i < r; i ++) {
            while(j < m && node[i].y >= node[j].y) {
                // 当涉及修改操作和查询操作时候
                // 一般Node内会有一个标识
                // 修改操作：if(node[j].type == 0) {
                //    fen.add(node[j].z, node[j].cnt)
                //}
                // 统计答案时也只需要对查询操作统计
                // 清空树状数组也是对修改操作
                fen.add(node[j].z, node[j].cnt);
                j++;
            }
            node[i].ans += fen.sum(node[i].z);
        }
        // 注意不能清空整个树状数组
        for (int t = l; t < j; t ++) {
            fen.add(node[t].z, -node[t].cnt);
        }
    };
    cdq(0, m);
    
    vector<int> res(n);
    for (int i = 0; i < m; i ++) {
        res[node[i].ans + node[i].cnt - 1] += node[i].cnt;
    }
    for (int i = 0; i < n; i ++) {
        cout << res[i] << '\n';
    }

    return 0;
}