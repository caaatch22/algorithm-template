#include <bits/stdc++.h>
#define endl '\n'
#define rep(i, a, b) for (int i = (a); i <= (b); i ++)
using namespace std;

const int N = 5e4 + 10, M = 2e5 + 10, S = 1e6 + 10; //值域

int n, A[N], ans[M], cnt[S], m, sq, cur;

struct query {
    int l, r, id;
    bool operator<(const query &rhs) const { //奇偶化排序
        if (l / sq != rhs.l / sq) 
            return l < rhs.l;
        if (l / sq & 1)
            return r < rhs.r;
        return r > rhs.r;
    }
} q[M];

void add(int p) {
    if(cnt[A[p]] == 0) cur++;
    cnt[A[p]]++;
}

void del(int p) {
    cnt[A[p]]--;
    if(cnt[A[p]] == 0) cur--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    sq = sqrt(n);
    rep(i, 1, n) cin >> A[i];
    cin >> m;
    rep(i, 1, m) {
        int l, r;
        cin >> l >> r;
        q[i] = {l, r, i};
    }
    sort(q + 1, q + 1 + m);

    int l = 1, r = 0;
    rep(i, 1, m) {
        while(l > q[i].l) add(--l);
        while(r < q[i].r) add(++r);
        while(l < q[i].l) del(l++);
        while(r > q[i].r) del(r--);
        ans[q[i].id] = cur;
    }
    rep(i, 1, m)  cout << ans[i] << endl;
    
    return 0;
}
