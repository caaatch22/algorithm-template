#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Edge {
	int u, v, w;
	bool operator<(const Edge&rhs) {
		return w > rhs.w;
	}
}

void solve() {
	int n, m, s;
	cin >> n >> m >> s;
	s--;
	vector<Edge> edges(m);
	vector<vector<int>> G(n);
	for (int i = 0; i < m; i ++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		edges[i] = {u, v, w};
	}
	sort(edges.begin(), edges.end());
	vector<bool> vis(n);
	vector<int> ans(n);
	auto bfs = [&](int u, int w) {
		vis[u] = 1;
		ans[u] = w;
	};

	for (auto [u, v, w]: edges) {
		G[u].push_back(v);
		bfs(u);
	}
	ans[s] = -1;
	for (int i = 0; i < n; i ++) {
		cout << ans[i] << " \n"[i == n - 1];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T = 1; // cin >> T;
	while(T --) {
		solve();
	}
	return 0;
}