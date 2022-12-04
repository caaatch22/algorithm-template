// p3195
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 50050;
int n, L;
ll dp[N], sum[N], f[N], g[N], h, t, Q[N];

long double slope(int i, int j) {
	return (long double) (dp[j] + g[j] - dp[i] - g[i]) / (f[j] - f[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> L;

    for(int i = 1; i <= n; i++) {
        cin >> sum[i];
        sum[i] += sum[i - 1];
        f[i] = sum[i] + i;
        g[i] = (f[i] + L + 1) * (f[i] + L + 1);
	}
	g[0] = (ll)(L + 1) * (L + 1);
    for(int i = 1; i <= n; i++) {
        while(h < t && slope(Q[h], Q[h + 1]) <= 2 * f[i]) h++;
		dp[i] = dp[Q[h]] + (f[i] - f[Q[h]] - L - 1) * (f[i] - f[Q[h]] - L - 1); 
		while(h < t && slope(Q[t], i) < slope(Q[t - 1], Q[t])) t--;
		Q[++t] = i;
    }

    cout << dp[n] << '\n';
    return 0;
}
