//luogu1850
#include <bits/stdc++.h>
using namespace std;

const double inf = 1e18;
const int N = 2010;
int G[310][310];
int n, m, v, e, c[N], d[N];
double k[N];
double f[N][N][2]; //f[i][j][0]走完i点，申请换了j次教室n点时体力耗费期望值最小

void floyd()
{
    for (int k = 1; k <= v; ++k)
        for (int i = 1; i <= v; ++i)
            for (int j = 1; j <= v; ++j)
                G[i][j] = min(G[i][k] + G[k][j], G[i][j]);
}


int main()
{
    
    cin >> n >> m >> v >> e;
    for (int i = 1; i <= n; i ++)  cin >> c[i];
    for (int i = 1; i <= n; i ++)  cin >> d[i];

    for (int i = 1; i <= n; i ++) cin >> k[i];

    memset(G, 0x3f, sizeof G);
    for (int i = 1; i <= e; i ++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        G[u][v] = G[v][u] = min(G[u][v], w);
    }
    
    floyd();

    for (int i = 1; i <= v; i ++)  G[i][i] = 0;

    for (int i = 0; i <= n; i ++)
        for (int j = 0; j <= m; j ++)
            f[i][j][0] = f[i][j][1] = inf;

    f[1][0][0] = f[1][1][1] = 0;

    for (int i = 2; i <= n; i ++)
    {
        f[i][0][0] = f[i - 1][0][0] + G[c[i - 1]][c[i]];
        for (int j = 1; j <= min(i, m); j++)
        {
            f[i][j][0] = min(f[i][j][0],
                         min(f[i - 1][j][0] + G[c[i - 1]][c[i]],
                         f[i - 1][j][1] + k[i - 1] * G[d[i - 1]][c[i]] + (1 - k[i - 1]) * G[c[i - 1]][c[i]]));
            f[i][j][1] = min(f[i][j][1], 
                         min(f[i - 1][j - 1][0] + (1 - k[i]) * G[c[i - 1]][c[i]] + k[i] * G[c[i - 1]][d[i]], 
                            f[i - 1][j - 1][1] + (1 - k[i - 1]) * (1 - k[i]) * G[c[i - 1]][c[i]]
                            +  (1 - k[i]) * k[i - 1] * G[d[i - 1]][c[i]]
                            + (1 - k[i - 1]) * k[i] * G[c[i - 1]][d[i]]
                            + k[i - 1] * k[i] * G[d[i - 1]][d[i]]));
        }
    }
    double res = inf;
    for (int j = 0; j <= m; j ++)
        res = min(res, min(f[n][j][0], f[n][j][1]));

    printf("%.2lf", res);

    return 0;
}