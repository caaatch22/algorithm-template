#include<bits/stdc++.h>
using namespace std;

const int N = 110;
const double eps = 1e-6;
int n;
double a[N][N];

int gauss()//高斯消元 O(n^3)
{
    int c, r;
    for(c = 0, r = 0; c < n; c ++)
    {
        int t = r;
        for(int i = r; i < n; i ++)//找到首元素最大
            if(fabs(a[i][c]) > fabs(a[t][c]))
                t = i;
                
        if(fabs(a[t][c]) < eps) continue;
        
        for(int i = c; i <= n; i ++) swap(a[t][i], a[r][i]);
        for(int i = n; i >= c; i --) a[r][i] /= a[r][c];
        for(int i = r + 1; i < n; i ++)
            if(fabs(a[i][c]) > eps)
                for(int j = n; j >= c; j --)
                    a[i][j] -= a[r][j] * a[i][c];
        r ++;
    }
    if(r < n)
    {
        for(int i = r; i < n; i ++)
            if(fabs(a[i][n]) > eps)
                return 2;
        return 1;
    }
    
    for(int i = n - 1; i >= 0; i --)
        for(int j = i + 1; j < n; j ++)
            a[i][n] -= a[i][j] * a[j][n];
    
    return 0;//有唯一解
}

int main()
{
    cin >> n ;
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n + 1; j ++) 
            cin >> a[i][j];
    
    int t = gauss();
    if(t == 0)
        for(int i = 0; i < n; i ++) printf("%.2f\n", a[i][n]);
    else if(t == 1)
        puts("Infinite group solutions");
    else puts("No solution");

    return 0;
}