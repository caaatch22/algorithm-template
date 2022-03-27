//acwing 867


#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
vector<pair<int, int>> pfac[N];
//预处理质因数（当需要经常1~N所有数的质因数时候）
void init() {
    for (int i = 2; i < N; i ++) {
        if(pfac[i].size()) continue;
        for (int j = i; j < N; j += i) {
            int t = j, cnt = 0;
            while(t%i == 0)  t/= i, cnt ++;
            pfac[j].push_back({i, cnt});
        }
    }
}

void decompose(int n)
{
    for (int i = 2; i <= n / i; i ++)
        if(n % i == 0) //then i is prime
        {
            int s = 0;
            while(n%i == 0)
            {
                n /= i;
                s++;
            }
            printf("%d %d\n", i, s);
        }
    if(n > 1)  printf("%d %d\n", n, 1);
    puts("");
}



int main()
{

    int n;
    cin >> n;
    while(n --)
    {
        int x;
        cin >> x;
        decompose(x);
    }
    return 0;
}