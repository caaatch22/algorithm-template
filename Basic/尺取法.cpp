/*
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int a[N], S, n, b[N];
//前缀和加二分o(nlogn)

int main()
{

    ios::sync_with_stdio(false), cin.tie(0);

    int T;
    cin >> T;
    while(T--)
    {
        cin >> n >> S;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            b[i] = b[i - 1] + a[i];
        }
        if(b[n] < S)
        {
            cout << 0 << endl;
            continue;
        }

        int res = n;
        for (int i = 1; b[i] + S <= b[n]; i++)
        {
            int t = lower_bound(b + i, b + n + 1, b[i] + S) - b - i;
            res = min(res, t);
        }
        cout << res << endl;
    }
    return 0;
}
*/

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int a[N], S, n;
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int T;
    cin >> T;
    while(T--)
    {
        cin >> n >> S;
        for (int i = 1; i <= n; i++)    cin >> a[i];

        int res = n + 1;

        int i = 1, j = 1, sum = 0;
        for (;;)//写的时候想着转换的图
        {
            while (sum < S && j <= n)
                sum += a[j++];

            if (sum < S) break; //退出条件，容易遗漏

            res = min(res, j - i);
            sum -= a[i++];
        }
        if(res > n)    res = 0;
        cout << res << endl;
    }
    return 0;
}