//acwing860 JudgeIfBiGraph

#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 1e5 + 10;
vector<int> G[N];
int n, m, clr[N];

bool dfs(int u, int c)
{
    clr[u] = c;
    for(auto v:G[u])
    {
        if(!clr[v])
            if(!dfs(v, 3-c)) return false;
        if(clr[v] == c) return false;
    }
    return true;
}


int main()
{
    cin >> n >> m;
    while(m -- )
    {
        int u, v; cin >> u >> v;
        G[u].pb(v), G[v].pb(u);
    }
    
    bool flg = true;
    for(int i = 1; i <= n; i ++)
    {
        if(!clr[i])
            if(!dfs(i, 1)) {flg = false; break;}
    }
    if(flg) cout << "Yes";
    else cout << "No";
    return 0;
}