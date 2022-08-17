#include <bits/stdc++.h>
using namespace std;
const int N = 1000100;
//单调栈， 记录每个数左边比他小（大）的第一个数（也可以记录其下标）
int stk[N], tt, a[N];

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int n;  cin >> n;
    for (int i = 1; i <= n; i ++)  cin >> a[i];

    for (int i = 1; i <= n; i++) {
        while(tt && stk[tt] >= a[i]) tt--;
        if(tt) cout << stk[tt] << ' ';
        else cout << -1 << ' ';
        stk[++tt] = a[i];
    }
    return 0;
}