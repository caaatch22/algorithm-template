//poj 1679
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e4 + 10;
struct Edge{
    int u, v, w;
    bool operator<(const Edge &rhs) const { return w < rhs.w; }
} edges[N];

int n, m, fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main()
{
    int T; scanf("%d", &T);
    while(T -- )
    {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i ++) fa[i] = i;
        
        for (int i = 1; i <= m; i ++)
        {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            edges[i] = {u, v, w};
        }
        sort(edges + 1, edges + 1 + m);
        
    }

    return 0
}