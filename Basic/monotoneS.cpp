#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010;

int stk[N], tt;

int main()
{
    int n;
    cin>>n;
    for(int i = 0; i < n; i++)
    {
        int x ;
        cin>>x;
        while(tt && stk[tt] >= x) tt--;
        if(tt) cout<<stk[tt]<<' ';
        else cout<<-1<<' ';
        stk[ ++ tt] = x;
    }
    
    return 0;
}