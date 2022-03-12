//最小(大)瓶颈树
//[noip2013货车运输]p1967  最大瓶颈树
// loj136  最小瓶颈树
//最小生成树+lca+倍增同时维护dis[N][17]
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 1e4 + 10, M = 5e4 + 10;
struct node{int v, w;};
vector<node> G[N];
int n, m, q;
struct Edge{
	int u, v, w;
	bool operator<(const Edge &rhs) const { return rhs.w < w; }
} edges[M];

int dep[N], fa[N][18], p[N], dis[N][18];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }

void bfs(int s)
{
	dep[0] = 0, dep[s] = 1;
	queue<int> q;
	q.push(s);
	while(q.size())
	{
		int u = q.front(); q.pop();
		for(auto nxt:G[u])
		{
			int v = nxt.v, w = nxt.w;
			if(dep[v] > dep[u] + 1)
			{
				dep[v] = dep[u] + 1;
				fa[v][0] = u;
				dis[v][0] = w;
				q.push(v);
				for (int i = 1; i <= 17; i ++)
				{
					fa[v][i] = fa[fa[v][i - 1]][i - 1];
					dis[v][i] = min(dis[v][i - 1], dis[fa[v][i - 1]][i - 1]);
				}
			}
		}
	}
}

int lca(int a, int b)
{
	int ans = 0x3f3f3f3f;
	if(dep[a] < dep[b]) swap(a, b);

	for (int k = 17; k >= 0; k --)
		if(dep[fa[a][k]] >= dep[b])
			ans = min(ans, dis[a][k]), a = fa[a][k];
	
	if(a == b) return ans;

	for (int k = 17; k >= 0; k --)
		if(fa[a][k] != fa[b][k])
		{
			ans = min(ans, min(dis[a][k], dis[b][k]));
			a = fa[a][k], b = fa[b][k];
		}

	ans = min(ans, min(dis[a][0], dis[b][0]));
	return ans;
}

void kruskal()
{
	for (int i = 1; i <= n; i ++)  p[i] = i;
	sort(edges + 1, edges + 1 + m);
	for(int i = 1;  i <= m; i ++)
	{
		int u = edges[i].u, v = edges[i].v, w = edges[i].w;
		if(find(u) != find(v))
		{
			p[find(u)] = find(v);
			G[u].pb({v, w}), G[v].pb({u, w});
		}
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i ++)
	{
		int u, v, w; scanf("%d %d %d", &u, &v, &w);
		edges[i] = {u, v, w};
	}

	kruskal();

	memset(dis, 0x3f, sizeof dis);
	memset(dep, 0x3f, sizeof dep);
	for (int i = 1; i <= n; i ++)
		if(dep[i] == 0x3f3f3f3f) bfs(i);
	

	scanf("%d", &q);
	while(q -- )
	{
		int s, t; scanf("%d %d", &s, &t);
		if(find(s) != find(t))  puts("-1");
		else printf("%d\n", lca(s, t));
	}

	return 0;
}