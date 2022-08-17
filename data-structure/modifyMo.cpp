#include <bits/stdc++.h>
#define endl '\n'
#define rep(i, a, b) for (int i = (a); i <= (b); i ++)
using namespace std;

const int N = 134000, S = 1e6 + 10; //值域

int n, m, mq, mc, len, cur;
int w[N], cnt[S], ans[N];
struct Query {
    int id, l, r, tim;
}q[N];
struct Modify {
    int pos, val;
} c[N];

int get(int x) {
    return x / len;
}

bool cmp(const Query& a, const Query& b) {
    int al = get(a.l), ar = get(a.r);
    int bl = get(b.l), br = get(b.r);
    if (al != bl) return al < bl;
    if (ar != br) return ar < br;
    return a.tim < b.tim;
}

void add(int val) {
    if(cnt[val] == 0) cur++;
    cnt[val]++;
}

void del(int val) {
    cnt[val]--;
    if(cnt[val] == 0) cur--;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    rep(i, 1, n) cin >> w[i];

    rep (i, 1, m) {
        char op[2];
        int a, b;
        cin >> op >> a >> b;
        if (*op == 'Q') mq ++, q[mq] = {mq, a, b, mc};
        else c[ ++ mc] = {a, b};
    }

    len = cbrt((double)n * max(1 , mc)) + 1;
    sort(q + 1, q + mq + 1, cmp);
    
    int l = 1, r = 0, t = 0;
    rep(i, 1, mq) {
        auto [id, ql, qr, qt] = q[i];
        while (l < ql) del(w[l++]);
        while (l > ql) add(w[--l]);
        while (r < qr) add(w[++r]);
        while (r > qr) del(w[r--]);
        while (t < qt) {
            t ++ ;
            if (ql <= c[t].pos && qr >= c[t].pos) {
                del(w[c[t].pos]);
                add(c[t].val);
            }
            swap(w[c[t].pos], c[t].val);
        }
        while (t > qt) {
            if (ql <= c[t].pos && qr >= c[t].pos) {
                del(w[c[t].pos]);
                add(c[t].val);
            }
            swap(w[c[t].pos], c[t].val);
            t--;
        }
        ans[id] = cur;
    }

    rep(i, 1, mq) printf("%d\n", ans[i]);
    return 0;
}
