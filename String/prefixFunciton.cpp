#include <bits/stdc++.h>
#define endl '\n'
#define pb push_back
#define rep(i, a, b) for (int i = (a); i <= (b); i ++) 

using namespace std;
using ll = long long;

vector<int> prefixFunction(string s) {
    int n = s.size();
    vector<int> p(n);
    for (int i = 1; i < n; i ++) {
        int j = p[i - 1];
        while(j > 0 && s[i] != s[j]) j = p[j - 1];
        if(s[i] == s[j]) ++j;
        p[i] = j;
    }
    return p;
}

// KMP based on prefixFunction. return all match postion in t
// s小串， t大串
vector<int> kmp(string s, string t) {
    vector<int> ans;
    int n = (int)s.size(), m = (int)t.size();
    if (n > m) return ans;
    auto p = prefixFunction(s);
    for (int i = 0, j = 0; i < m; ++i) {
        while (j > 0 && s[j] != t[i])  j = p[j - 1];
        if (s[j] == t[i] && ++j == n)
            ans.emplace_back(i - n + 1);
    }
    return ans;
}

void solve() {
    string s1, s2;
    cin >> s1 >> s2;
    auto p = kmp(s2, s1);
    for (auto i:p)
        cout << i + 1 << '\n';
    p = prefixFunction(s2);
    rep(i, 0, p.size() - 1) {
        cout << p[i] << " \n"[i == p.size() - 1];
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