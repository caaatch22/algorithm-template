//luogu p3201

// 如果我们把1染成2并且|S1|>|S2|,
// 那么我们应该把 22 接到 11 的后面。
// 这样会有一个问题：本次修改后这个链的颜色是1(颜色为2的链被删除了)，
// 如果接下来修改颜色2(显然这是合法的)，会使得找不到颜色2而只能找到颜色1了。
// 所以我们需要使用一个now数组，表示当我们要寻找颜色now时，实际上需要寻找颜色为now[x]的链。
// 如果遇到上面这种情况就要交换交换now[x], now[y];
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int col[N], now[N], n, m, ans;
vector<int> idx[N];

void d_merge(int x, int y) {
    for(auto i:idx[x]) {
        if(col[i - 1] == y)  ans --;
        if(col[i + 1] == y)  ans --; 
    }
    for(int i:idx[x]) col[i] = y;
    for (int i:idx[x]) idx[y].push_back(i);
    idx[x].clear();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) {
        cin >> col[i];
        now[col[i]] = col[i];
        if(col[i] != col[i - 1])  ans ++;
        idx[col[i]].push_back(i);
    }
    while(m --) {
        int op, x, y;
        cin >> op;
        if(op == 2) cout << ans << '\n';
        else {
            cin >> x >> y;
            if(x == y)  continue;
            if(idx[now[x]].size() > idx[now[y]].size()) swap(now[x], now[y]);
            d_merge(now[x], now[y]);
        }
    }

    return 0;
}