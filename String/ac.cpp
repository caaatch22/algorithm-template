//luogu3808
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int n;
char s[N];

namespace ac
{

int tr[N][26], fail[N], idx;
queue<int> q;
int cnt[N];

void insert(char* s) {
    int p = 0;
    for (int i = 1; s[i]; ++i) {
        int u = s[i] - 'a';
        if(!tr[p][u])  tr[p][u] = ++idx;
        p = tr[p][u];
    }
    ++cnt[p];
}

void build() {
    for (int i = 0; i < 26; ++i)
        if(tr[0][i]) q.push(tr[0][i]);
    
    while(q.size()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < 26;  i++) {
            if(tr[u][i])
                fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]); //原本这个tr[fail[u]][i]可能不存在（为0）
                                                                   // 但是下一步else做了一个优化（类似于路径压缩）
            else
                tr[u][i] = tr[fail[u]][i];
        }
    }
}

int query(char *s) {
    int u = 0, res = 0;
    for (int i = 1; s[i]; ++i) {
        u = tr[u][s[i] - 'a'];
        for (int j = u; j && cnt[j] != -1; j = fail[j])
            res += cnt[j], cnt[j] = -1;
    }
    return res;
}

}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) {
        scanf("%s", s + 1);
        ac::insert(s);
    }
    ac::build();
    scanf("%s", s + 1);
    printf("%d\n", ac::query(s));
    return 0;
}