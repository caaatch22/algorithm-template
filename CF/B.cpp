#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1010;
int n, a[N];

int pw(int a, int b)
{
    ll res = 1;
    for (int i = 1; i <= b; i ++)
        res *= a;
    return res;
}

int main()
{
    int T; scanf("%d", &T);
    while(T -- )
    {
        cin >> n;
        if(n <= 19) 
        {
            puts("Yes");
            for (int i = 1; i <= n; i ++) printf("%d ", pw(3, i - 1));
        }
        else
            printf("No\n");
    }

    return 0;
}