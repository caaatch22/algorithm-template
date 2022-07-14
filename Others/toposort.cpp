// acwing164 reachabiliry 
// biset optimization
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 3e4 + 10;
int n, m;
vector<int> G[N];
bitset<N> dis[N];
int topo[N], ind[N];

void topo_sort() {
    int cnt = 0;
    queue<int> q;
    for(int i = 1; i <= n; i ++) 
        if(ind[i] == 0) q.push(i);
        
    while(q.size()) {
        int u = q.front();q.pop();
        topo[cnt ++] = u;
        for(auto v:G[u])
            if(--ind[v] == 0) q.push(v);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    while(m -- ) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].pb(v);
        ind[v] ++;
    }
    
    topo_sort();
    
    for(int i = n - 1; i >= 0; --i) {
        int u = topo[i];
        dis[u][u] = 1;
        for(auto v : G[u])
            dis[u] |= dis[v];
    }
    
    for(int i = 1; i <= n; i ++) cout << dis[i].count() << '\n';
    return 0;
}


/*
#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 3e4 + 10;
bitset<N> dis[N];

void floyd() {
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(dis[i][j])
                dis[i] |= dis[j];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i ++) dis[i][i] = 1;
    while(m -- ) {
        int u, v;
        scanf("%d %d", &u, &v);
        dis[u][v] = 1;
    }
    floyd();
    for(int i = 1; i <= n; i ++) printf("%d\n", dis[i].count());
    return 0;
}
*/