#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 1e5 + 10, inf = 0x3f3f3f3f;
struct node{int v, w;};
vector<node> G[N];
int dis[N], n, m;
bool inq[N];

void spfa() {
    memset(dis, 0x3f, sizeof dis);
    dis[1] = 0;
    inq[1] = 1;
    queue<int> q;
    q.push(1);
    while(q.size()) {
        int u = q.front(); q.pop();
        inq[u] = 0;
        for(auto [v, w]:G[u]) {
            if(dis[v] > w + dis[u]) {
                dis[v] = dis[u] + w;
                if(!inq[v])
                    q.push(v), inq[v] = true;
            }
        }
    }
}

int main() {
    cin >> n >> m;
    while(m -- ) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].pb({v, w});
    }
    spfa();
    if(dis[n] == inf)    cout << "impossible";
    else        cout << dis[n];
    return 0;
}