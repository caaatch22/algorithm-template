//poj3041
//O(V*E)
// classic and great problem
//view the asteroids as edge, and the weapon rays as vertex
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 510;
int G[N][N];
int n, k, p[N], vis[N];

bool match(int u)
{
    for (int i = 1; i <= n; i ++)
    {
        if(G[u][i] && !vis[i])
        {
            vis[i] = true;
            if(p[i] == 0 || match(p[i]))
            {
                p[i] = u;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    scanf("%d %d", &n, &k);
    while(k --)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        G[x][y] = 1;
    }

    int res = 0;
    for (int i = 1; i <= n; i ++)
    {
        memset(vis, 0, sizeof vis);
        if(match(i)) res++;
    }

    printf("%d\n", res);

    return 0;
}