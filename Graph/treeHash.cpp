#include <bits/stdc++.h>

using ull = unsigned long long;
const ull mask = std::chrono::steady_clock::now().time_since_epoch().count();

ull shift(ull x) {
    x ^= mask;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= mask;
    return x;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    auto G = std::vector<std::vector<int>>(n);
    for (int i = 1; i < n; i ++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    std::vector<ull> hash_vals(n);
    std::unordered_set<ull> trees;
    std::function<void(int, int)> dfs = [&](int u, int fa) {
        hash_vals[u] = 1;
        for (const auto v: G[u]) {
            if(v == fa) continue;
            dfs(v, u);
            hash_vals[u] += shift(hash_vals[v]);
        }
        trees.insert(hash_vals[u]);
    };

    dfs(0, -1);
    // 求有根树下不同构的子树
    std::cout << trees.size() << '\n';

    return 0;
}