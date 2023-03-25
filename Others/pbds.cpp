#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
// use this as multiset with find_by_order
using RBT = __gnu_pbds::tree<pair<ll, int>, null_type, less<pair<ll, int>>, rb_tree_tag, tree_order_statistics_node_update>;
RBT rbt;
int t = 0;
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    std::vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < m; i ++) {
        rbt.insert({a[i], t++});
    }

    int count = 0;
    std::vector<ll> res(n);
    ll kth = 0;
    for (auto it = rbt.begin(); count < k; count++, it++) {
        res[m - 1] += it->first;
        kth = it->first;
    }

    for (int i = m; i < n; i ++) {
        rbt.erase(rbt.lower_bound({a[i - m], 0}));
        rbt.insert({a[i], t++});
        auto new_kth = rbt.find_by_order(k - 1)->first;
        if (a[i - m] <= kth && a[i] <= kth) {
            res[i] = res[i - 1] + (-a[i - m] + a[i]);
        } else if (a[i - m] > kth && a[i] <= kth) {
            res[i] = res[i - 1] - kth + a[i];
        } else if (a[i - m] <= kth && a[i] > kth) {
            res[i] = res[i - 1] + new_kth - a[i - m];
        }
        else if (a[i - m] > kth && a[i] > kth) {
            res[i] = res[i - 1];
        }
        kth = new_kth;
    }
    
    for (int i = m - 1; i < n; i ++) {
        std::cout << res[i] << ' ';
    }
    return 0;
}