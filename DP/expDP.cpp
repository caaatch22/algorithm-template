//acw217
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 1e5 + 10;
struct node{int v, w;};
vector<node> G[N];
int n, m, oud[N];
double f[N]; //f[i]:从i跳到n的期望长度

double dp(int u)
{
    if(f[u] >= 0) return f[u];
    if(u == n)  return f[u] = 0;

    f[u] = 0;
    for(auto nxt:G[u])
    {
        int v = nxt.v, w = nxt.w;
        f[u] += (w + dp(v)) / oud[u];
    }
    return f[u];
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m;
    while(m -- )
    {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].pb({v, w});
        oud[u]++;
    }
    memset(f, -1, sizeof f);
    printf("%.2lf\n", dp(1));

    return 0;
}