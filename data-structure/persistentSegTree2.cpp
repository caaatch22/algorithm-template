// http://oj.daimayuan.top/course/10/problem/464
// 在给定 N 长的数组 {A} 中进行 Q 次询问 [Li,Ri] 区间中不大于 Hi 的元素个数。
//主席树的在线做法 还有树状数组的对询问离线做法
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, q, L[N], R[N], idx, H[N], rt[N], a[N];
vector<int> alls;

struct node {
    int l, r, cnt;
} t[N * 75];

int insert(int now, int l, int r, int x) {
    int p = ++idx;
    t[p] = t[now];
    if(l == r) {
        t[p].cnt++;
        return p;
    }
    int mid = l + r >> 1;
    if(x <= mid) t[p].l = insert(t[now].l, l, mid, x);
    else t[p].r = insert(t[now].r, mid + 1, r, x);
    t[p].cnt = t[t[p].l].cnt + t[t[p].r].cnt;
    return p;
}

int query(int version, int l, int r, int h) {
    if(l == r)  return t[version].cnt;

    if(r <= h) return t[version].cnt;
    int mid = l + r >> 1, res = 0;
    res += query(t[version].l, l, mid, h);
    if(h > mid) res += query(t[version].r, mid + 1, r, h);
    return res;
}

int build(int l, int r) {
    int p = ++ idx;
    if (l == r) return p;
    int mid = l + r >> 1;
    t[p].l = build(l, mid), t[p].r = build(mid + 1, r);
    return p;
}

int find(int x) { return lower_bound(alls.begin(), alls.end(), x) - alls.begin(); }

void init() {
    idx = 0;
    memset(rt, 0, sizeof rt);
    alls.clear();
    memset(t, 0, sizeof t);
}

int main() {
    int T; scanf("%d", &T);
    while(T --) {
        init();
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i ++) {
            scanf("%d", &a[i]);
            alls.push_back(a[i]);
        }
        //虽然是在线做法，但为了好处理h离散化后的值，就将Hi也加入alls
        for (int i = 1; i <= q; i ++) {
            scanf("%d%d%d", &L[i], &R[i], &H[i]);
            alls.push_back(H[i]);
        }
        sort(alls.begin(), alls.end());
        alls.erase(unique(alls.begin(), alls.end()), alls.end());
        
        //rt[0] = build(0, alls.size() - 1);
        for (int i = 1; i <= q; i ++) H[i] = find(H[i]);
        for (int i = 1; i <= n; i ++) a[i] = find(a[i]);

        for (int i = 1; i <= n; i ++)
            rt[i] = insert(rt[i - 1], 0, alls.size() - 1, a[i]);
        
        
        for (int i = 1; i <= q; i++)  {
            printf("%d ", query(rt[R[i]], 0, alls.size() - 1, H[i]) 
                        - query(rt[L[i] - 1], 0, alls.size() - 1, H[i]));
        }
        puts("");
    }
    return 0;
}