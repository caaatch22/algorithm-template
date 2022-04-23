#include<bits/stdc++.h>
#define pb push_back
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;

struct node {
	int l, r;
	ll add, sum;
} t[N << 2];
int n, m, w[N], nw[N];
vector<int> G[N];

int dep[N], top[N], son[N], dfn[N], sz[N], fa[N], cnt;
////////////////////////线段树部分/////////////////////////

void pushdown(int p) {
	auto &rt = t[p], &nl = t[p << 1], &nr = t[p << 1 | 1];
	if(rt.add) {
		nl.add += rt.add, nl.sum += (ll)(nl.r - nl.l + 1) * rt.add;
		nr.add += rt.add, nr.sum += (ll)(nr.r - nr.l + 1) * rt.add;
		rt.add = 0;
	}
}

void pushup(int p) { t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum; }

void build(int p, int l, int r) {
	t[p] = {l, r, 0, nw[l]};
	if(l == r) return;
	
	int mid = l + r >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}

ll query(int p, int l, int r) {
	if(t[p].l >= l && t[p].r <= r) return t[p].sum;
	
	pushdown(p);
	int mid = t[p].l + t[p].r >> 1;
	ll res = 0;
	if(l <= mid)  res += query(p << 1, l, r);
	if(r > mid)  res += query(p << 1 | 1, l ,r);
	//pushup(p);
	return res;
}

void modify(int p, int l, int r, int k) {
	if(t[p].l >= l && t[p].r <= r) {
		t[p].sum += (t[p].r - t[p].l + 1) * k;
		t[p].add += k;
		return;
	}
	
	pushdown(p);
	int mid = t[p].l + t[p].r >> 1;
	if(l <= mid) modify(p << 1, l, r, k);
	if(r > mid) modify(p << 1 | 1, l , r, k);
	pushup(p);
}

////////////////////////树剖部分///////////////////////////
//第一次dfs 维护sz, 重儿子， dep[], fa[]
void dfs1(int u, int fath) {

	sz[u] = 1, dep[u] = dep[fath] + 1, fa[u] = fath;
	for(int v:G[u])
	{
		if(v == fath) continue;
		dfs1(v, u);
		sz[u] += sz[v];
		if(sz[son[u]] < sz[v]) son[u] = v;
	}
}
//第二次dfs， 维护dfs序，
void dfs2(int u, int tp) {

	dfn[u] = ++cnt, nw[cnt] = w[u], top[u] = tp;
	if(!son[u]) return;
	dfs2(son[u], tp); //递归重儿子
	//维护轻儿子信息
	for(int v:G[u]) {
		if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}

void modify_path(int u, int v, int k) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		modify(1, dfn[top[u]], dfn[u], k);
		u = fa[top[u]];
	}
	if(dep[u] < dep[v]) swap(u, v);
	modify(1, dfn[v], dfn[u], k);
}

void modify_tree(int u, int k) {
	modify(1, dfn[u], dfn[u] + sz[u] - 1, k);
}

ll query_tree(int u) {
	return query(1, dfn[u], dfn[u] + sz[u] - 1);
}

ll query_path(int u, int v) {
	ll res = 0;
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		res += query(1, dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	if(dep[u] < dep[v]) swap(u, v);
	res += query(1, dfn[v], dfn[u]);
	return res;
}

////////////////////////////////////////////////////////////
int main() {

	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) scanf("%d", &w[i]);
	for(int i = 1; i < n; i ++) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].pb(v), G[v].pb(u);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	
	build(1, 1, n);
	
	scanf("%d", &m);
	while(m -- ) {
		int op, u, v, k;
		scanf("%d%d", &op, &u);
		
		if(op == 1) {
			scanf("%d%d", &v, &k);
			modify_path(u, v, k);
		}
		else if(op == 2) {
			scanf("%d", &k);
			modify_tree(u, k);
		}	
		else if(op == 3) {
			scanf("%d", &v);
			printf("%lld\n", query_path(u, v));
		}
		else 
			printf("%lld\n", query_tree(u));
			
	}

	return 0;
}