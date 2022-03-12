//p4551 

#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 1e5 + 10, M = 1e5 * 31 + 10;
int son[M][2], idx, res, dis[N];
struct node{ int v, w; };
vector<node> G[N];


void insert(int x)
{
    int p = 0;
    for (int i = 30; i >= 0; --i)
    {
        int u = (x >> i) & 1;
        if(!son[p][u])  son[p][u] = ++idx;
        p = son[p][u];
    }
}

void update(int x)
{
    int tmp = 0;
    for (int i = 30, p = 0; i >= 0; --i)
    {
        int u = (x >> i) & 1;
        if(son[p][u ^ 1])
            p = son[p][u ^ 1], tmp |= (1 << i);
        else
            p = son[p][u];
    }
    res = max(res, tmp);
}

void dfs(int u, int fa)
{
    insert(dis[u]);
    update(dis[u]);
    for(auto nxt:G[u])
    {
        int v = nxt.v, w = nxt.w;
        if(v == fa)  continue;
        dis[v] = dis[u] ^ w;    //awesome
        dfs(v, u);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; i ++) 
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        G[u].pb({v, w}), G[v].pb({u, w});
    }

    dfs(1, 0);
    printf("%d\n", res);

    return 0;
}