#include <bits/stdc++.h>
using namespace std;
//fa[N][0]其实就是nxt[]
const int N = 1e6 + 10;
char s[N];
int n, fa[N][22], dep[N];

inline void getnxt()
{
    for (int i = 2, j = 0; i <= n; i ++)
    {
        while(j && s[i]!= s[j + 1])  j = fa[j][0];
        if(s[i] == s[j + 1])  j ++;
        fa[i][0] = j, dep[i] = dep[j] + 1;
    }
}

int main()
{
    fa[0][0] = fa[1][0] = 0, dep[0] = 0, dep[1] = 1;
    scanf("%s", s + 1);
    n = strlen(s + 1);

    getnxt();

    for (int i = 1; i <= 21; i ++)
        for (int j = 1; j <= n; j ++)
            fa[j][i] = fa[fa[j][i - 1]][i - 1];

    int m;   scanf("%d", &m);
    while(m -- )
    {
        int a, b;  scanf("%d%d", &a, &b);
        if(dep[a] < dep[b])  swap(a, b);
        for (int k = 21; k >= 0; k--)
            if(dep[fa[a][k]] >= dep[b])
                a = fa[a][k];
        //if(a == b) {printf("%d\n", dep[a]); continue;}
        for (int k = 21; k >= 0; k --)
            if(fa[a][k] != fa[b][k])
                a = fa[a][k], b = fa[b][k];
        printf("%d\n", fa[a][0]);
    }

    return 0;
}