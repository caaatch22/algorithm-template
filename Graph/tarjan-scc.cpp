#include<bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 1e4 + 10;
vector<int> G[N], G2[N];
stack<int> s;
int n, m, tim, scc_cnt;
int w[N], dfn[N], low[N], id[N];
int dist[N], ind[N], W[N];
bool ins[N];

void tarjan(int u) {
    low[u] = dfn[u] = ++tim;
    s.push(u);  ins[u] = true;

    for(int v:G[u]) {
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[v], low[u]);
        }
        else if(ins[v])
            low[u] = min(low[u], dfn[v]);
    }

    if(low[u] == dfn[u]) {
        int y;  ++scc_cnt;
        do {
            y = s.top(); s.pop(); 
            ins[y] = false;
            id[y] = scc_cnt;
            W[scc_cnt] += w[y];
        } while (y != u);
    }
}

int sol() {

    queue<int> q;
    for (int i = 1; i <= scc_cnt; i++)
        if(!ind[i]) {
            q.push(i);
            dist[i] = W[i];
        }

    while(q.size()) {
        //cout << "cnt = " << ++cnt << endl;
        int u = q.front();  q.pop();
        for (int v:G2[u]) {
            //当有重边时， dist[v]被更新的值始终不变， 即dist[v] = dist[u] + W[v]; 所以不会影响
            dist[v] = max(dist[v], dist[u] + W[v]);
            if(--ind[v] == 0)
                q.push(v);
        }
    }

    int ans = 0;
    for (int i = 1; i <= scc_cnt; i++)
        ans = max(ans, dist[i]);
    return ans;
}


int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i ++)    cin >> w[i];
    while(m--) {
        int u, v;
        cin >> u >> v;
        G[u].pb(v);
    }
    for (int i = 1; i <= n; i ++)
        if(!dfn[i])
            tarjan(i);
    //缩点
    for (int u = 1; u <= n; ++u) {
        for(int v : G[u]) {
            if(id[v] != id[u]) {
                G2[id[u]].pb(id[v]);
                ind[id[v]]++;
                //printf("ind[%d] = %d\n",id[v], ind[id[v]]);
            }
        }
    }
    // debug
    // for (int i = 1; i <= scc_cnt; i++)
    //     printf("ind[%d] = %d\n",i, ind[i]);
    // for (int i = 1; i <= scc_cnt; i++)
    // {
        
    //     printf("%d->", i);
    //     for (int v:G2[i])
    //         printf("%d ", v);
    //     puts("");
    // }
    printf("%d\n", sol());
    return 0;
}