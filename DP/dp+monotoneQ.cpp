#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define rep(i, a, b) for(int i = (a); i <= (b); i ++) 
using namespace std;
using ll = long long;
using P = pair<int, int>;

const int N = 1e5 + 10;
ll pref[N], dp[N];
int q[N], n, m;

ll calc(int i) {
    return dp[max(0, i - 1)] - pref[i];
}

void solve() {
    cin >> n >> m;
    rep(i, 1, n) cin >> pref[i], pref[i] += pref[i - 1];

    int hh = 0, tt = 0; q[0] = 0;
    rep(i, 1, n) {
        while(hh <= tt && calc(i) >= calc(q[tt]))  tt --;
        q[++tt] = i;
        while(hh <= tt && i - q[hh] > m)  hh ++;
        dp[i] = pref[i] + calc(q[hh]);
    }
    cout << dp[n] << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1; // cin >> T;
    while(T --) {
        solve();
    }
    return 0;
}