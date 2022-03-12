#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e6 + 10;
int q[N], a[N], n, k;

int main()
{
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i ++)  scanf("%d", &a[i]);

    int head = 0, tail = 0;

    for (int i = 1; i < k; i ++) {
        while(head <= tail && a[q[tail]] >= a[i]) tail --;
        
    }

        return 0;
}