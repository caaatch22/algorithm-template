#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

struct SuffixAutomaton {
    static constexpr int ALPHABET_SIZE = 26, N = 1e5;
    struct Node {
        int len;
        int link;
        int next[ALPHABET_SIZE];
        Node() : len(0), link(0), next{} {}
    } t[2 * N];
    int cntNodes;
    SuffixAutomaton() {
        cntNodes = 1;
        fill(t[0].next, t[0].next + ALPHABET_SIZE, 1);
        t[0].len = -1;
    }
    int extend(int p, int c) {
        if (t[p].next[c]) {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1)
                return q;
            int r = ++cntNodes;
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            copy(t[q].next, t[q].next + ALPHABET_SIZE, t[r].next);
            t[q].link = r;
            while (t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = ++cntNodes;
        t[cur].len = t[p].len + 1;
        while (!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        return cur;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    string A;
    cin >> A;
    int p = 1;
    SuffixAutomaton sam;
    for (auto c : A) {
        p = sam.extend(p, c - 'a');
    }
    
    vector<int> w(m);
    for (int i = 0; i < m; i++) {
        cin >> w[i];
    }
    
    vector<i64> s(m + 1);
    for (int i = 0; i < m; i++) {
        s[i + 1] = s[i] + w[i];
    }
    
    while (k--) {
        string B;
        cin >> B;
        
        int p = 1;
        i64 ans = 0;
        deque<int> q{0};
        for (int i = 0, j = 0, len = 0; i < m; i++) {
            while (j < m && sam.t[p].next[B[j] - 'a']) {
                p = sam.t[p].next[B[j] - 'a'];
                len++;
                j++;
                while (!q.empty() && s[j] > s[q.back()]) {
                    q.pop_back();
                }
                q.push_back(j);
            }
            while (q.front() < i) {
                q.pop_front();
            }
            ans = max(ans, s[q.front()] - s[i]);
            len--;
            if (len <= sam.t[sam.t[p].link].len) {
                p = sam.t[p].link;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
