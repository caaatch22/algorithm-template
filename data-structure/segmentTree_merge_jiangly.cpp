// codeforces600E
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

namespace SegTree {

struct Info {
    ll cnt, ans; // 颜色的个数，颜色编号和
    Info(ll v = 0, ll x = 0) : cnt(v), ans(x) {}
};

Info operator+(const Info& a, const Info& b) {
    if(a.cnt > b.cnt) {
        return a;
    } else if(a.cnt < b.cnt) {
        return b;
    } else {
        return Info(a.cnt, a.ans + b.ans);
    }
}

Info merge(const Info &a, const Info &b) {
    return a + b;
}

struct Node {
    Node *l,*r;
    Info val;
    Node() : l(nullptr), r(nullptr), val() {}
};

void pull(Node *&p) {
    p->val = merge(p->l == nullptr ? Info() : p->l->val, p->r == nullptr ? Info() : p->r->val);
}

// query(t, 0, n, query_left, query_right)
Info query(Node *t, int l, int r, int le, int ri) { // [le, ri)
    //   l    r
    // ooxxxxxooo
    // L R LR L R
    // xxooxooxxo
    if(ri <= l || r <= le || t == nullptr) {
        return Info();
    }
    if(le <= l && r <= ri) {
        return t->val;
    }
    int m = (l + r) / 2;
    return merge(query(t->l, l, m, le, ri), query(t->r, m, r, le, ri));
}

void modify(Node *&t, int l, int r, int x, int v) { // [l,r)
    if(t == nullptr) {
        t = new Node();
    }
    if(r - l == 1) {
        t->val.cnt += v;
        t->val.ans = x;
        return;
    }

    int m = (l + r) / 2;
    if(x < m) {
        modify(t->l, l, m, x, v);
    }else {
        modify(t->r, m, r, x, v);
    }
    pull(t);
}

Node* merge(Node *&t, Node *&o, int l, int r) { // [l,r)
    if(t == nullptr) return o;
    if(o == nullptr) return t;

    Node *p = new Node();

    if(r - l == 1) {
        p->val = t->val;
        p->val.cnt += o->val.cnt;
        return p;
    }

    int m = (l + r) / 2;
    p->l = merge(t->l, o->l, l, m);
    p->r = merge(t->r, o->r, m, r);
    pull(p);
    return p;
}

}

using namespace SegTree;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> col(n);
    for (int i = 0; i < n; i ++) {
        cin >> col[i];
    }
    vector<Node *> rt(n + 1, nullptr);
    vector<vector<int>> G(n);
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<ll> ans(n);
    function<void(int, int)> dfs = [&](int u, int fa) {
        modify(rt[u], 1, n + 1, col[u], 1);
        for (auto v:G[u]) {
            if(v == fa) continue;
            dfs(v, u);
            rt[u] = merge(rt[u], rt[v], 1, n + 1);
        }
        ans[u] = rt[u]->val.ans;
    };
    dfs(0, -1);
    for (int i = 0; i < n; i ++) {
        cout << ans[i] << " \n"[i == n - 1];
    }

    return 0;
}