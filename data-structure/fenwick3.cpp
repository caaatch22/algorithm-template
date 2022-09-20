//离散化+数值域上的树状数组
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e4 + 10;
int n, a[N], tr[N], L[N], R[N];
ll t[N];

int lowbit(int x) { return x & -x; }
void add(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i))
        tr[i] += v;
}
int query(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
        res += tr[i];
    return res;
}

int main() {
    scanf("%d", &n);
    vector<ll> alls(n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &t[i]);
        alls.push_back(t[i]);
    }
    /*19~23行离散化*/
    sort(alls.begin(), alls.end());
    alls.erase(unique(alls.begin(), alls.end()), alls.end());

    for (int i = 1; i <= n; i ++)
        a[i] = lower_bound(alls.begin(), alls.end(), t[i]) - alls.begin() + 1;

    ll res = 0;

    
    for (int i = 1; i <= n; i ++) {
        L[i] = query(a[i] - 1);  //L[i]: i左侧有多少点小于a[i]
        add(a[i], 1);
    }
    memset(tr, 0, sizeof tr);
    for (int i = n; i; i --) {
        R[i] = n - i - query(a[i]);
        add(a[i], 1);
    }

    // for (int i = 1; i <= n; i ++)
    //     printf("R[%d] = %d\n", i, R[i]);

    for (int i = 2; i <= n - 1; i ++)
        res += (ll)L[i] * R[i];
    
    cout << res;
    return 0;
}