// 状压dp
#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;
    auto d = std::vector<std::vector<int>>(n, std::vector<int>(n));
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            std::cin >> d[i][j];
        }
    }
    // floyd
    for (int k = 0; k < n; k ++) {
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
                d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    constexpr int inf = 1e9;
    int s = 1 << n;
    auto dp = std::vector<std::vector<int>>(n, std::vector<int>(s));
    std::for_each(dp.begin(), dp.end(), [=](auto &f)
                  { std::fill(f.begin(), f.end(), inf); });

    dp[0][1] = 0;
    // 一般 枚举状态， 枚举当前节点，枚举pre结点
    // 
    for (int i = 1; i < s; i ++) {
        // current node
        for (int u = 0; u < n; u ++) {
            if (!((i >> u) & 1)) continue;

            int last_s = i ^ (1 << u);
            for (int pre = 0; pre < n; pre ++) {
                if (!((last_s >> pre) & 1)) continue;
                if (dp[pre][last_s] == inf) continue;
                dp[u][i] = std::min(dp[u][i], dp[pre][last_s] + d[pre][u]);
            }
        }
    }

    int ans = inf;
    for (int i = 1; i < n; i ++) {
        ans = std::min(ans, dp[i][s - 1] + d[i][0]);
    }
    std::cout << ans << '\n';
    return 0;
}