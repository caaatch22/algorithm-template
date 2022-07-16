//poj2395瓶颈生成树
//最小生成树是瓶颈生成树的一种
//但瓶颈生成树不一定是最小生成树
#include <bits/stdc++.h>
using namespace std;
const int N = 2010, M = 1e5 + 10;
int n, m, fa[N];

struct Edge{
    int u, v, w;
    bool operator < (const Edge &rhs) const { return w < rhs.w; }
} edge[M];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
/*
//二分做法
bool check(int x) {
    for (int i = 1; i <= n; i ++) fa[i] = i;

    int cnt = 0;
    for (int i = 1; i <= m; i ++) {
        int u = edge[i].u, v = edge[i].v, w = edge[i].w;
        if(w > x) break;
        if(find(u)!= find(v)) {
            fa[find(u)] = find(v);
            cnt++;
        }
    }

    return cnt >= n - 1;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i ++)
        scanf("%d %d %d", &edge[i].u, &edge[i].v, &edge[i].w);
    sort(edge + 1, edge + 1 + m);

    int l = 1, r = 1e4;
    while(l < r) {
        int mid = l + r >> 1;
        if(check(mid))  r = mid;
        else l = mid + 1;
    }
    cout << n - 1 << ' ' << l;
    return 0;
}

*/

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i ++)
        scanf("%d %d %d", &edge[i].u, &edge[i].v, &edge[i].w);
    sort(edge + 1, edge + 1 + m);

    for (int i = 1; i <= n; i ++)  fa[i] = i;
        
    int res = 0;
    for (int i = 1; i <= m; i++) {
        int u = edge[i].u, v = edge[i].v, w = edge[i].w;
        if(find(u) != find(v)) {
            fa[find(u)] = find(v);
            res = max(res, w);
        }
    }
    cout << res;
    return 0;
}