#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
char str[N];
int son[N][26], cnt[N], idx;

void insert(char *str)
{
    int p = 0;
    for (int i = 0; str[i]; i ++)
    {
        int u = str[i] - 'a';
        if(!son[p][u])  son[p][u] = ++idx;
        p = son[p][u];
    }
    ++cnt[p];
}

int query(char *str)
{
    int p = 0;
    for (int i = 0; str[i]; ++i)
    {
        int u = str[i] - 'a';
        if(!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}

int main()
{
    int T;
    cin >> T;
    while(T -- )
    {
        char op[2];
        scanf("%s%s", op, str);
        if(*op == 'I')  insert(str);
        else printf("%d\n", query(str));
    }
}

/*
#include <bits/stdc++.h>
using namespace std;

const int N = 2e4 + 10;
unordered_map<string, int> cnt;

int main()
{
    int n;
    scanf("%d", &n);
    while(n -- )
    {
        char op[2]; scanf("%s", op);
        string s; cin >> s;
        if(*op == 'I') cnt[s] ++;
        else 
        {
            if(cnt.find(s) == cnt.end())
                puts("0");
            else
                printf("%d\n", cnt[s]);
        }
    }
    return 0;
}

*/