//分层图最短路
//luogu4568
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 2e4 + 10;
int n, m, s, t, k, dis[N][11];
struct node{int v, w;};
vector<node> G[N];
bool vis[N][11];

struct node1 {
    int v, w, cnt;
    bool operator<(const node1 &rhs) const { return w > rhs.w; }
};

void dij() {
    priority_queue<node1> q;
    memset(dis, 0x3f, sizeof dis);
    dis[s][0] = 0;
    q.push({s, 0, 0});
    while(q.size()) {
        const auto t = q.top(); q.pop();
        int u = t.v, cur_cnt = t.cnt;
        if(vis[u][cur_cnt]) continue;
        vis[u][cur_cnt] = 1;
        for(auto nxt:G[u]) {
            int v = nxt.v, w = nxt.w;
            if(cur_cnt < k && dis[v][cur_cnt + 1] > dis[u][cur_cnt]) {
                dis[v][cur_cnt + 1] = dis[u][cur_cnt];
                q.push({v, dis[v][cur_cnt + 1], cur_cnt + 1});
            }
            if(dis[v][cur_cnt] > dis[u][cur_cnt] + w) {
                dis[v][cur_cnt] = dis[u][cur_cnt] + w;
                q.push({v, dis[v][cur_cnt], cur_cnt});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m >> k >> s >> t;
    s++, t++;

    while(m --) {
        int u, v, w;
        cin >> u >> v >> w;
        u++, v++;
        G[u].pb({v, w}), G[v].pb({u, w});
    }
    dij();
    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= k; i ++)
        ans = min(ans, dis[t][i]);

    cout << ans;
    return 0;
}