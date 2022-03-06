//acwing 849

#include <bits/stdc++.h>
using namespace std;

const int N = 510, inf = 0x3f3f3f3f;
int dis[N], G[N][N], n, m;
bool vis[N];

void dij()
{
    memset(dis, 0x3f, sizeof dis); dis[1] = 0;
    for (int j = 0; j < n; j ++)
    {
        int minv = inf, pos = -1;
        for(int i = 1; i <= n; i ++)
            if (!vis[i] && minv > dis[i])
                minv = dis[i], pos = i;
        
        if(pos == -1) break;
        vis[pos] = 1;
        for (int i = 1; i <= n; i ++)
            if(!vis[i] && dis[pos] + G[pos][i] < dis[i])
                dis[i] = dis[pos] + G[pos][i];
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    memset(G, 0x3f, sizeof(G));
    while(m --)
    {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        G[u][v] = min(G[u][v], w);
    }
    
    dij();
    
    cout << (dis[n] == inf ? -1 : dis[n]);
    return 0;
}