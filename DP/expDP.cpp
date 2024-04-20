/**
 * 题意：有向无环图，从1号点到n号点，每个点有若干个出边，
 * 每条边有一个权值，求从1号点到n号点的期望距离。
 */
#include <bits/stdc++.h>

struct node {
  int v, w;
};

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  cin >> n >> m;
  auto f = std::vector<double>(n);
  auto oud = std::vector<int>(n);
  auto G = std::vector<std::vector<node>>(n);
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    G[u].emplace_back(v, w);
    oud[u]++;
  }

  std::fill(f.begin(), f.end(), -1);
  std::function<double(int)> dp = [&](int u) -> double {
    if (f[u] >= 0) return f[u];
    if (u == n) return f[u] = 0;

    f[u] = 0;
    for (auto [v, w] : G[u]) {
      f[u] += (w + dp(v)) / oud[u];
    }
    return f[u];
  };
  std::cout << std::fixed << std::setprecision(2) << dp(0) << '\n';

  return 0;
}
/**
 * 若还有自环（但是无其他环）
 * dp(u) = \frac{w_{uu}}{oud[u]} dp(u) + \sum_{v, v!=u}
 * \frac{w_{uv}}{oud[u]}dp(v)
 * 需要将dp(u)移项到左侧，然后化简
 */