//acwing788 reverse pair

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
int a[N], n, tmp[N];

ll merge_sort(int l, int r)
{
    if(l >= r) return 0;

    int mid = l + r >> 1;
    ll ans = merge_sort(l, mid) + merge_sort(mid + 1, r);

    int k = 0, i = l, j = mid + 1;
    while(i <= mid && j <= r) 
    {
        if(a[i] <= a[j]) tmp[k++] = a[i++];
        else 
        {
            tmp[k++] = a[j++];
            ans += mid - i + 1;
        }
    }
    while(i <= mid) tmp[k++] = a[i++];
    while(j <= r)   tmp[k++] = a[j++];
    for (int i = l, j = 0; i <= r; i ++, j ++) a[i] = tmp[j];
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    printf("%lld\n", merge_sort(0, n - 1));
    return 0;
}