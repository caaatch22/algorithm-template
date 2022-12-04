#include <bits/stdc++.h>

using namespace std;

constexpr int N = 2e5;

struct ACM {

    int state_num;
    struct Node {
        array<int, 26> nxt;
        int fail;
        Node(): nxt{}, fail(0) {}
    };
    vector<Node> vec;
    ACM(int n) : vec(n + 1) {}
    int insert(const string& s) {
        int p = 0;
        for (auto ch: s) {
            int &u = vec[p].nxt[ch - 'a'];
            if(!u) {
                u = ++state_num;
            }
            p = u;
        }
        return p;
    }
    void build() {
        queue<int> q;
        for(auto i: vec[0].nxt) {
            if(i) q.push(i);
        }
        while(q.size()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < 26; i ++) {
                int &v = vec[u].nxt[i];
                int w = vec[vec[u].fail].nxt[i];
                if(v) {
                    vec[v].fail = w;
                    q.push(v);
                } else {
                    v = w;
                }
            }
        }
    }

};

void solve() {
    int n;
    cin >> n;
    vector<string> patterns(n);
    ACM ac(N);

    vector<int> id(n); // id[i]表示第i个字符串结尾的state_num
    for (int i = 0; i < n; i ++) {
        cin >> patterns[i];
        id[i] = ac.insert(patterns[i]);
    }
    ac.build();
    // cerr << "state_num == " << ac.state_num << '\n';
    // for (int i = 1; i <= ac.state_num; i ++) {
    //     cerr << i << ".fail = "<< ac.vec[i].fail << "\n";
    // }
    // cerr << "/////////////////" << '\n';

    vector<vector<int>> G(ac.state_num + 1);
    for (int i = 1; i <= ac.state_num; i ++) {
        G[ac.vec[i].fail].push_back(i);
    }

    string t;
    cin >> t;

    int u = 0;
    vector<int> cnt(ac.state_num + 1);
    for (auto ch: t) {
        u = ac.vec[u].nxt[ch - 'a'];
        cnt[u]++;
        // cerr << u << '\n';
    }
    
    function<void(int)> dfs = [&](int u) {
        for (auto v: G[u]) {
            dfs(v);
            cnt[u] += cnt[v];
        }
    };
    dfs(0);
    // cerr << "///////////////////////" << '\n';
    for (int i = 0; i < n; i++) {
        cout << cnt[id[i]] << '\n';
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1; // cin >> T;
    while(T --) {
        solve();
    }
    return 0;
}