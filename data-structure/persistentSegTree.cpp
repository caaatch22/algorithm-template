//luogu 3824 kth-number
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, M = (N << 2) + 17 * N;

struct node {
    int l, r;
    int cnt;
} t[M];
int idx, a[N];
vector<int> num;
int find(int x) { return lower_bound(num.begin(), num.end(), x) - num.begin(); }

int insert(int now, int l, int r, int x) {
    int p = ++ idx;
    t[p] = t[now];
    if (l == r) {
        t[p].cnt ++ ;
        return p;
    }
    int mid = l + r >> 1;
    if(x <= mid) t[p].l = insert(t[now].l, l, mid, x);
    else t[p].r = insert(t[now].r, mid + 1, r, x);
    t[p].cnt = t[t[p].l].cnt + t[t[p].r].cnt;

    return p;
}

int build(int l, int r) {
    int p = ++ idx;
    if (l == r) return p;
    int mid = l + r >> 1;
    t[p].l = build(l, mid), t[p].r = build(mid + 1, r);
    return p;
}

int query(int x, int y, int l, int r, int k) {
    if(l == r) return l;
    int cnt = t[t[y].l].cnt - t[t[x].l].cnt;
    int mid = l + r >> 1;
    if(k <= cnt) return query(t[x].l, t[y].l, l, mid, k);
    else return query(t[x].r, t[y].r, mid + 1, r, k - cnt);
}

int n, m, root[N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) {
        scanf("%d", &a[i]);
        num.push_back(a[i]);
    }

    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());

    root[0] = build(0, num.size() - 1);

    for (int i = 1; i <= n; i ++ )
        root[i] = insert(root[i - 1], 0, num.size() - 1, find(a[i]));
    while (m -- ) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", num[query(root[l - 1], root[r], 0, num.size() - 1, k)]);
    }

    return 0;
}
