#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int n, tot;
ll win;

int main()
{
    int T; scanf("%d", &T);
    while(T -- )
    {
        cin >> n;
        win = (2 << ((ll)n - 1)) - 1;
        cout << win << '\n';
    }

    return 0;
}