//acwing 867


#include <bits/stdc++.h>
using namespace std;

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