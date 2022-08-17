#include <bits/stdc++.h>
#define pb push_back
#define endl '\n'
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
using namespace std;

const int N = 2050;

vector<int> G[N];
int n, m, k;

int f[N];

int sg(int u) {
    if(f[u] != -1) return f[u];

    unordered_set<int> s;
    for (auto v:G[u]) {
        s.insert(sg(v));
    }
    for (int i = 0;; i ++) 
        if(!s.count(i))
            return f[u] = i;
        
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        G[u].pb(v);
    }

    memset(f, -1, sizeof f);
    int res = 0;
    rep(i, 1, k) {
        int u;
        cin >> u;
        res ^= sg(u);
    }
    if(res)  cout << "win" << endl;
    else cout << "lose" << endl;

    return 0;
}