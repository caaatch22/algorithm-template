//hnoi2013 p3232
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 510;
struct node{int v, w;};
vector<node> G[N];
int n, m, deg[N];
double f[N]; //f[i]:从i跳到n的期望长度

double dp(int u)
{
    if(f[u] >= 0) return f[u];
    if(u == n) return f[u] = 0;

    f[u] = 0;
    for(auto nxt:G[u])
    {
        int v = nxt.v, w = nxt.w;
        f[u] += (w + dp(v)) / deg[u];
    }
    return f[u];
}

int main()
{

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i ++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ++deg[u], ++deg[v];
    }



    return 0;
}