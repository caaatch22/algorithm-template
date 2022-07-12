#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N = 2e5 + 10;
int val[N], lson[N], rson[N], dis[N];
int fa[N], idx, n;
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

bool cmp(int x, int y) { return val[x] == val[y] ? x < y : val[x] < val[y]; }

int merge(int x, int y) {
    if(!x || !y) return x + y;
    if(cmp(y, x)) swap(x, y);
    rson[x] = merge(rson[x], y);
    if(dis[rson[x]] > dis[lson[x]]) swap(lson[x], rson[x]);
    dis[x] = dis[rson[x]] + 1;
    return x;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    val[0] = 2e9;
    while(n --) {
        int op, x, y;  cin >> op;
        if(op == 1) {
            cin >> x;
            val[++idx] = x;
            fa[idx] = idx;
            dis[idx] = 1;
        }
        else if(op == 2) {
            cin >> x >> y;
            x = find(x), y = find(y);
            if(x != y) {
                if(cmp(y, x)) swap(x, y); //x为较小的
                fa[y] = x;
                merge(x, y);
            }
        }
        else if(op == 3) {
            cin >> x;
            cout << val[find(x)] << endl;
        }
        else { // 删除x所在堆的最小值
            cin >> x; x = find(x);
            if(cmp(rson[x], lson[x])) swap(lson[x], rson[x]);
            fa[x] = lson[x], fa[lson[x]] = lson[x];
            merge(lson[x], rson[x]);
        }
    }
    return 0;
}