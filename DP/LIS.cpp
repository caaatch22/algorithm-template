//最长上升子序列
//n^2做法  (转移可拓展)
// int main() {

//     const int N = 1e3 + 10;
//     f[N] = {0};
//     cin >> n;
//     for(int i = 1; i <= n; i ++)  cin >> a[i];
    
//     for(int i = 1; i <= n; i ++)
//     {
//         f[i] = 1;
//         for(int j = 1; j < i; j ++)
//             if(a[j] < a[i]) f[i] = max(f[i], f[j] + 1);
//     }
    
//     int res = 0;
//     for(int i = 1; i <= n; i ++)  res = max(res, f[i]);
//     cout << res;
    
//     return 0;
// }


//同时求了最长上升子序列和最长下降子序列
#include <bits/stdc++.h>

using namespace std;
const int N = 100100;
int n, len;
int a[N], q[N];

int main() {

    cin >> n;
    for (int i = 1; i <= n; i ++)  cin >> a[i];

    int pos = 0;
    q[0] = a[1];
//stl: 
    //最长严格上升子序列
    for (int i = 2; i <= n; i ++) {
        if (a[i] > q[pos])   //若改成a[i] >= q[pos]则是最长不下降子序列
            q[++pos] = a[i];
        else
            *lower_bound(q, q + pos + 1, a[i]) = a[i];
    }
    cout << pos + 1 << endl;

    // 最长严格下降子序列：
    pos = 0;
    q[0] = a[1];
    for (int i = 2; i <= n; i ++) {
        if (a[i] < q[pos])  //若改成a[i] <= q[pos]则是最长不上升子序列
            q[++pos] = a[i];
        else
            *lower_bound(q, q + pos + 1, a[i], greater<int>()) = a[i]; //注意不能是upper_bound()
    }
    cout << pos + 1 << endl;

//手写二分

    //最长严格上升子序列
    pos = 0, q[0] = a[1];
    for (int i = 2; i <= n; i ++) {
        if (a[i] > q[pos])    //若改成a[i] >= q[pos]则是最长不下降子序列, 下面的也要改成 if(q[mid] <= a[i]) l = mid + 1;
            q[++pos] = a[i];	
		else {
            int l = 0, r = pos;
            while(l < r) {
                int mid = l + r >> 1;
                if(q[mid] < a[i]) l = mid + 1;
                else r = mid;
            }
            q[l] = a[i];
            
        }
    }
    cout << pos + 1 << endl;

    pos = 0, q[0] = a[1];
    for (int i = 2; i <= n; i++) {
        if (a[i] < q[pos])  //若改成a[i] >= q[pos]则是最长不上升子序列,下面的也要改成 if(q[mid] > a[i]) l = mid + 1
            q[++pos] = a[i];		
		else {
            int l = 0, r = pos;
            while(l < r) {
                int mid = (l + r) >> 1;
                if(q[mid] > a[i]) l = mid + 1;
                else r = mid;
            }
            q[l] = a[i];
        }
    }

    cout << pos + 1 << endl;

    return 0;
}
  