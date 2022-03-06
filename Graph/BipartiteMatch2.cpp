#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 10000 + 10;
int n, t, dx[] = {-1, 0, 0, 1}, dy[] = {0, 1, -1, 0};
vector<int> G[N];
int w[N], p[N];
bool vis[N];

bool match(int u)
{
    for(auto v:G[u])
    {
        if(!vis[v])
        {
            vis[v] = true;
            if(p[v] == 0 || match(p[v]))
            {
                p[v] = u;
                return true;
            }
        }
    }
    return false;
}

int get_id(int x, int y) {return (x - 1)* n + y;}

int main()
{
    cin >> n >> t;
    while(t -- )
    {
        int x, y;
        cin >> x >> y;
        w[get_id(x, y)] = 1;
    }
    
    for(int i = 1; i <= n; i ++)
    {
        for(int j = 1; j <= n; j ++)
        {
            int id = get_id(i, j);
            if(w[id]) continue;
            for(int k = 0; k < 4; k ++)
            {
                int x = i + dx[k], y = j + dy[k];
                if(x < 1 || y < 1 || x > n || y > n) continue;
                int id2 = get_id(x, y);
                //cout << id2 << endl;
                if(!w[id2])    G[id].pb(id2);
            }
        }
    }
    
    int res = 0;
    for(int i = 1; i <= n * n; ++i)
    {
        memset(vis, 0, sizeof(vis));
        if(match(i)) res ++;
    }
    cout << res / 2;
    
    return 0;
}