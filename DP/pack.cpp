#include<bits/stdc++.h>
using namespace std;

void pack01 {
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 1), w(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> v[i] >> w[i];     // volume, weight
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = m; j >= v[i]; j --) {
            f[j] = max(f[j, f[j - v[i]]] + w[i]);
            // 求方案 f[j] += f[j - a[i]];
        }
    }
    cout << f[m] << '\n';
}

void completePack {
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 1), w(n + 1);
    for(int i = 1; i <= n; i++)   cin >> v[i] >> w[i];

    // vector<vector<int>> f(n + 1, vector<int>(m + 1));
    // for(int i = 1; i <= n; i++)
    //     for(int j = 0; j <= m; j++) {
    //         if(j < v[i]) f[i][j] = f[i - 1][j];
    //         else f[i][j] = max(f[i - 1][j],f[i][j - v[i]] + w[i] );
    //     }
    // cout << f[n][m] << '\n';
    for(int i = 1; i <= n; i++) {
        for(int j = v[i]; j <= m; j ++) { // 正序循环，表示i->i转移，每个物品用无限次
            f[j] = max(f[j],f[j - v[i]] + w[i] );
            // 方案数： f[j] = f[j] + f[j - w[i]]
        }
    }
    cout << f[m] << '\n';
    return 0;
}

// 多重背包，分组背包 见进阶指南 p280

int main() {

    return 0;
}