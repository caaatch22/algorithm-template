//最长上升子序列

//1. n^2做法
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int f[N], a[N], n;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i ++)  cin >> a[i];
    
    for(int i = 1; i <= n; i ++)
    {
        f[i] = 1;
        for(int j = 1; j < i; j ++)
            if(a[j] < a[i]) f[i] = max(f[i], f[j] + 1);
    }
    
    int res = 0;
    for(int i = 1; i <= n; i ++)  res = max(res, f[i]);
    cout << res;
    
    return 0;
}

//2. 维护类似单调递增的队列
//stl （若是要求最长下降序列，需要用lower_bound(q, q + pos + 1, a[i], greater<int>())）
//不能同upper_bound()
/*
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100010;
int a[N], d1[N], d2[N], n;
int main() 
{
	while (cin >> a[++n])
        ;
    n--;                       
    int len1 = 1, len2 = 1;		
	d1[1] = a[1];		
	d2[1] = a[1];

    for (int i = 2; i <= n; i++)
    {		
		if (d1[len1] >= a[i])
            d1[++len1] = a[i]; 
        else 
            *upper_bound(d1 + 1, d1 + 1 + len1, a[i], greater<int>()) = a[i];
		
		if (d2[len2] < a[i]) d2[++len2] = a[i];		
		else
            *lower_bound(d2 + 1, d2 + 1 + len2, a[i]) = a[i];

	}
	cout << len1 << endl << len2;		
	return 0;		
}
*/
//一下求了最长上升子序列和最长下降子序列
#include<iostream>
#include<cstdio>
using namespace std;
const int N=100100;
int n, len;
int a[N], q1[N], q2[N];

int main()
{
    while(scanf("%d",&a[++n]) == 1)
        ;
    n--;
    q1[0] = a[1];
    q2[0] = a[1];

    int pos1 = 0, pos2 = 0;
    for (int i = 2; i <= n; i++)
    {	
		if (q1[pos1] >= a[i]) q1[++pos1] = a[i];		
		else 
        {
            int l = 0, r = pos1, mid;
            while(l < r)
            {
                mid = (l + r) >> 1;
                if(q1[mid] >= a[i]) l = mid + 1;
                else r = mid;
            }
            q1[l] = a[i];
        }

        if (q2[pos2] < a[i]) q2[++pos2] = a[i];	
		else
        {
            int l = 0, r = pos2, mid;
            while(l < r)
            {
                mid = l + r >> 1;
                if(q2[mid] < a[i]) l = mid + 1;
                else r = mid;
            }
            q2[l] = a[i];
            
        }
    }

	cout << pos1 + 1 << endl << pos2 + 1;
   
    return 0;
}
  