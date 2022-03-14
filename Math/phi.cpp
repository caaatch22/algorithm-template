#include <bits/stdc++.h>
using namespace std;

/*phi compute 
根据给定n 计算phi(n) O(aqrt(n))
核心公式 phi(n) = n*(1-1/p1)*(1 - 1/p2)*...
*/
int get_phi(int n)
{
    int res = n;
    for (int i = 2; i <= n / i; i++)
    {
        if(n % i == 0)
        {
            res = res / i * (i - 1); // res *= (1 - 1/n)
            while(n % i == 0)   n /= i;
        }
    }
    if(n > 1)  res = res / n * (n - 1);
    return res;
}

typedef long long ll;
const int N = 1e6 + 10;

int phi[N], prime[N];
bool vis[N]; //合数true

void sel_phi(int n)
{
    int cnt = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i ++)
    {
        if(!vis[i]) 
        {
            prime[cnt++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; prime[j] <= n / i; j ++)
        {
            vis[prime[j] * i] = true;
            if(i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else
                phi[prime[j] * i] = phi[i] * (prime[j] - 1);
        }
    }
}

int main()
{

}