// 求树上 对某个点来说包含他的连通点集个数
#include <bits/stdc++.h>
#define pb push_back
#define endl '\n'
using ll = long long;
using namespace std;
const int N = 1e6 + 10, mod = 1e9 + 7;

ll f[N], ans[N], n;
vector<int> G[N];

ll qpow(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void dfs(int u, int fa) {
    f[u] = 1;
    for (auto v:G[u]) {
        if(v == fa) continue;
        dfs(v, u);
        f[u] = f[u] * (f[v] + 1) % mod;
    }
}

/*
考虑换根，ans[u]记为以u为根，和整棵树其他点能形成的所有子树数量。（即最终答案）
换根方程：ans[v]=( ans[u]/(f[v]+1) +1)*f[v]  
解释：u 点答案除以v点贡献(f[v] + 1) 为与v无关的u点答案，+1后为其余点对v点贡献，再乘上f[v]

有一个很坑的地方，就是(f[v]+1)求逆元可能得到0 (f[v]可能为 mod-1)，这时相当于除于0，出错
当逆元inv为0时，ans[u]实际是由在树形dp的时候求出的f[u]，而f[u]又等于(他所有儿子f的值+1)的乘积。
所以ans[u] / (f[v]+1)又可以变成u的其他儿子的乘积：u除 v 外的其他儿子记brother。
(f[brother_1]+1) * (f[brother_2] + 1) * .....他的所有兄弟的值乘积。
*/

void dp(int u, int fa) {
    for (int v:G[u]) {
        if(v == fa) continue;
        ll inv = qpow(f[v] + 1, mod - 2);
        if(inv) ans[v] = (ans[u] * inv % mod + 1) % mod * f[v] % mod;
        else {
            ll t = 1;
            for (auto other:G[u]) {
                if(other == v || other == fa) continue;
                t = t * (f[other] + 1) % mod;
            }
            ans[v] = (t + 1) * f[v] % mod;
        }
        dp(v, u);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i < n; i ++) {
        int u, v; cin >> u >> v;
        G[u].pb(v), G[v].pb(u);
    }
    dfs(1, 0);
    ans[1] = f[1];
    dp(1, 0);
    
    for (int i = 1; i <= n; i ++) cout << ans[i] << endl;
    return 0;
}