#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10,M = N * 31;
int a[N];
int son[M][2], idx;

void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; --i) {
        int u = ( (x>>i) & 1);
        if(!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
}
// 集合内和x异或的最大值
int query(int x) {
	int p = 0, res = 0;
	for (int i = 30; i >= 0; --i) {
		int u = (x >> i) & 1;
		if(son[p][u ^ 1]) p = son[p][u ^ 1], res |= (1 << i);
		else p = son[p][u];
        // 集合内和x异或的最小值
        // if(son[p][u])  p = son[p][u];  
        // else res |= (1 << i), p = son[p][u ^ 1];
	}
    return res;
}

int main() {
    int n, res = 0;
    cin >> n;
    for(int i = 0; i < n; i++)  cin >> a[i];
    for(int i = 0; i < n; i++) {
        insert(a[i]);
        res = max(res, query(a[i]));
    }
    cout << res;
    return 0;
}