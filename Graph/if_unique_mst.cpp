#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define endl "\n"
using namespace std;

const int N = 200010;

int n, m, k;
struct edge {
    int l, r, w;
    bool operator<(const edge& rhs) { return w < rhs.w; }
} ed[N];
int p[N];
int find(int x) { return p[x] == x ? p[x] : p[x] = find(p[x]); }

void solve() {
    cin >> n >> m;
    rep(i, 1, n) p[i] = i;
    rep(i, 1, m) {
        int a, b, c; cin >> a >> b >> c;
        ed[i].l = a, ed[i].r = b, ed[i].w = c;
    }
    sort(ed + 1, ed + 1 + m);

    int res = 0, ans = 0;
    rep(i, 1, m) {
        int r = i;
        while (r <= m && ed[i].w == ed[r].w) r++;
        r--;
        for (int j = i; j <= r; j++) {
            int a = find(ed[j].l), b = find(ed[j].r);
            if (a ^ b) res += ed[j].w;
        }

        for (int j = i; j <= r; j++) {
            int a = find(ed[j].l), b = find(ed[j].r);
            if (a ^ b) {
                p[a] = b;
                ans += ed[j].w;
            }
            //之后再正常最小生成树即可
        }
        i = r;
        //处理区间
    }

    if (res == ans) cout << ans << endl;
    else cout << "Not Unique!\n";
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr), cout.tie(nullptr);
    int T = 1; cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
