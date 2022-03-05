#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, a[N];

#define lowbit(x) (x)&(-x)

int main()
{
    
    cin >> n;
    while(n -- )
    {
        int t, ans = 0;
        cin >> t;
        while(t)
        {
            t -= lowbit(t);
            ans++;
        }
        cout << ans << ' ';
    }
    // while(n -- )
    // {
    //     int t;
    //     cin >> t;
    //     cout << __builtin_popcount(t) << ' ';
    // }
    
    
    return 0;
}