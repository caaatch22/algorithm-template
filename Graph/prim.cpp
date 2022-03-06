//acwing858
#include <bits/stdc++.h>
using namespace std;

const int N = 510, inf = 0x3f3f3f3f;
int G[N][N], dis[N];
int n, m;
bool vis[N];

int prim()
{
    int res = 0;
    memset(dis, 0x3f, sizeof dis);
    dis[1] = 0;   //随便选一点进入mst集合
    for(int j = 0; j < n; j ++)
    {
        int minv = inf, pos = -1;
        for(int i = 1; i <= n; i ++)
            if(!vis[i] && dis[i] < minv)
                pos = i, minv = dis[i];
                
        if(pos == -1) return inf;
        vis[pos] = true;
        res += dis[pos];
        
        for(int i = 1; i <= n; i ++)
            if(!vis[i] && dis[i] > G[pos][i])
                dis[i] = G[pos][i];
    }
    return res;
}

int main()
{
    cin >> n >> m;
    memset(G, 0x3f, sizeof(G));
    while(m --)
    {
        int u, v, w;
        cin >> u >> v >> w;
        G[u][v] = G[v][u] = min(G[u][v], w);
    }
    
    int res = prim();
    if(res > inf/2) cout << "impossbile";
    else cout << res;
    
    return 0;
}