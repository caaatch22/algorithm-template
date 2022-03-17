#include <bits/stdc++.h>
using namespace std;

const int N = 20010;
int n;
char s[160][80], t[1000010];

namespace ac
{
int tr[N][26], fail[N], idx;
queue<int> q;
int mark[N], ans[N];

void insert(char *s, int num)
{
    int p = 0;
    for (int i = 0; s[i]; i ++)
    {
        int u = s[i] - 'a';
        if(!tr[p][u])  tr[p][u] = ++idx;
        p = tr[p][u];
    }
    mark[p] = num;
}

void build()
{
    for (int i = 0; i < 26; ++i)
        if(tr[0][i]) q.push(tr[0][i]);
    
    while(q.size())
    {
        int u = q.front(); q.pop();
        for (int i = 0; i < 26;  i++)
        {
            if(tr[u][i])
                fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]); 
            else
                tr[u][i] = tr[fail[u]][i];
        }
    }
}


void query(char *s)
{
    int u = 0;
    for (int i = 0; s[i]; ++i)
    {
        u = tr[u][s[i] - 'a'];
        for (int j = u; j; j = fail[j])
            ans[mark[j]]++;
    }
}

void init()
{
    memset(fail, 0, sizeof fail);
    memset(tr, 0, sizeof tr);
    memset(mark, 0, sizeof mark);
    memset(ans, 0, sizeof ans);
    idx = 0;
}

}



int main()
{
    while(cin >> n && n)
    {
        ac::init();
        for (int i = 1; i <= n;  i++)
        {
            scanf("%s", s[i]);
            ac::insert(s[i], i);
        }
        scanf("%s", t);
        ac::build();
        ac::query(t);
        int maxv = 0;
        for (int i = 1; i <= n; i ++)
            maxv = max(maxv, ac::ans[i]);
        printf("%d\n", maxv);
        for (int i = 1; i <= n; i++)
            if (ac::ans[i] == maxv)
                printf("%s\n", s[i]);
    }
    return 0;
}