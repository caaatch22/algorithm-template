//基环树森林求直径和最大
#include <bits/stdc++.h>
#define endl '\n'
#define pb push_back
using ll = long long;
using namespace std;
const int N = 1e6 + 10, M = N << 1;
int h[N], e[M], w[M], ne[M], idx;
ll s[N], sum[M], d[M]; //环上的前缀和数组, 破环成链后两倍的前缀和
bool ins[N], vis[N];
int n, cir[M], ed[M], cnt; //cnt环的个数
int fa[N], fw[N]; //父节点， 反向权值
int q[M];
ll ans;

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

//深搜+栈 找环
void dfs(int u, int from) {
    vis[u] = ins[u] = true;
    for (int i = h[u]; ~i; i = ne[i]) {
        //如果是反向边则跳过，必须用边来判断，这样才能确定是通过反向变回到父节点
        if (i == (from ^ 1)) continue; 
        int v = e[i];
        fa[v] = u, fw[v] = w[i];
        if (!vis[v]) dfs(v, i);
        else  if(ins[v]) {
            cnt++;
            ed[cnt] = ed[cnt - 1];
            ll tot = w[i];
            for (int k = u; k != v; k = fa[k])  {
                s[k] = tot;
                tot += fw[k];
                cir[++ ed[cnt]] = k;
            }
            s[v] = tot, cir[++ ed[cnt]] = v;
        }
    }
    ins[u] = false;
}

// 求以u为根节点的子树的最大深度
ll dfs_d(int u)  {
    vis[u] = true;
    ll d0 = 0, d1 = 0; //最大距离，次大距离
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (vis[v]) continue;
        ll d = dfs_d(v) + w[i];
        if (d >= d0) d1 = d0, d0 = d;
        else if (d > d1) d1 = d;
    }
    ans = max(ans, d1 + d0);
    return d0;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    memset(h, -1, sizeof h);
    for (int u = 1; u <= n; u ++) {
        int v; ll w; cin >> v >> w;
        add(u, v, w), add(v, u, w);
    }

    for (int i = 1; i <= n; i ++) 
        if(!vis[i])                                                                  
            dfs(i, -1);

    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; i ++) vis[cir[i]] = 1; //标记环上所有点

    ll res = 0;
    for (int i = 1; i <= cnt; i ++) {
        ans = 0; // 当前基环树的直径
        int sz = 0; // 当前基环树的环的大小
        for (int j = ed[i - 1] + 1; j <= ed[i]; j ++) {
            int k = cir[j];
            d[sz] = dfs_d(k); // 求以当前点为根的子树的最大深度
            sum[sz] = s[k];
            sz++;
        }
        // 破环成链，前缀和数组和d[]数组延长一倍
        for (int j = 0; j < sz; j ++)
            d[sz + j] = d[j], sum[sz + j] = sum[j] + sum[sz - 1];
    
        // 做一遍滑动窗口，比较依据是d[k] - sum[k]
        int hh = 0, tt = -1;
        for (int j = 0; j < sz * 2; j++) {
            while (hh <= tt && q[hh] <= j - sz) hh++;
            if (hh <= tt) ans = max(ans, d[j] + sum[j] + d[q[hh]] - sum[q[hh]]);
            while (hh <= tt && d[j] - sum[j] >= d[q[tt]] - sum[q[tt]]) tt--;
            q[ ++ tt] = j;
        }
        res += ans;
    }
    cout << res << endl;
    return 0;
}