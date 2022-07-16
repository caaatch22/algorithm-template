#include<bits/stdc++.h>
using namespace std;

const int N = 22000010;
char s[N], a[N];
int p[N], n;

void init() {
    int k = 0;
    s[k++] = '$', s[k++] = '#';
    for (int i = 0; i < n; i ++ ) s[k ++ ] = a[i], s[k ++ ] = '#';
    s[k ++ ] = '^';
    n = k;
}

void manacher() {
    int mr = 0, mid;
    for (int i = 1; i < n; i ++) {
        if(i < mr)  p[i] = min(p[mid * 2 - i], mr - i);
        else  p[i] = 1;
        while(s[i - p[i]] == s[i + p[i]])   p[i]++;
        if(i + p[i] > mr) {
            mr = i + p[i];
            mid = i;
        }
    }
}

int main() {
    scanf("%s", a);
    n = strlen(a);
    init();
    manacher();
    int res = 0;
    for (int i = 0; i < n; i ++)   res = max(res, p[i]);
    cout << res - 1;
    return 0;
}