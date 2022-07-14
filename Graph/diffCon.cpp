//最小值求最长路
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 1e5 + 10;

typedef long long ll;
struct node{int v, w;};
vector<node> G[N];
ll dist[N];
int n, m, cnt[N];
bool inq[N];

bool spfa() {
    stack<int> s;
    memset(dist, -0x3f, sizeof(dist));
    dist[0] = 0;
    s.push(0);
    inq[0] = true;
    
    while(s.size()) {
        int u = s.top(); s.pop();
        inq[u] = false;
        
        for(auto nxt:G[u]) {
            int v = nxt.v, w = nxt.w;
            if(dist[v] < dist[u] + w) {
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n + 1)  return false;
                if(!inq[v]) {
                    s.push(v);
                    inq[v] = true;
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    while (m -- ) {
        int x, u, v;
        scanf("%d%d%d", &x, &u, &v);
        if(x == 1) G[u].pb({v, 0}),G[v].pb({u, 0});
        else if(x == 2) G[u].pb({v, 1});
        else if(x == 3) G[v].pb({u, 0});
        else if(x == 4) G[v].pb({u, 1});
        else G[u].pb({v, 0});
    }
    
    for(int i = 1; i <= n; i++) G[0].pb({i, 1});
    
    if(!spfa()) puts("-1");
    else {
        ll res = 0;
        for(int i = 1; i <= n; i++) res += dist[i];
        printf("%lld\n", res);
    }   
    return 0;
}