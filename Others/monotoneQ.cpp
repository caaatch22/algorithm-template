#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int a[N], q[N],n, k;
//滑动窗口
int main() {
    cin >> n >> k;
    for(int i = 0; i < n; i++)   cin >> a[i];
    int hh = 0, tt = -1;
    for(int i = 0; i < n; i++) {
        //判断队头是否已经划出窗口
        if( hh <= tt && i - k + 1  > q[hh]) hh++;
        while(hh <= tt && /*后面改成要维护的最小值*/a[q[tt]] >= a[i]) tt -- ;//求区间最小
        q[ ++ tt ] = i;
        if(i >= k-1) printf("%d ",a[q[hh]]);
        
    }
    return 0;
}