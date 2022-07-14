//poj2406
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
char s[N];
int nxt[N], n;
/*
//区间l->r的kmp
    nxt[l] = 0;
    for (int i = l + 1; i <= r; i ++) {
        int j = nxt[i - 1];
        while(j && s[i] != s[l + j])   j = nxt[l + j - 1];
        if(s[i] == s[j + l])  j++;
        nxt[i] = j;
    }
*/
void get_nxt() {
    nxt[1] = 0;
    for (int i = 2, j = 0; i <= n; i ++) {
        while(j && s[i] != s[j + 1]) j = nxt[j];
        if(s[i] == s[j + 1]) j++;
        nxt[i] = j;
    }
}

int main() {
    while(~scanf("%s", s + 1)) {
        if(s[1] == '.')  break;
        n = strlen(s + 1);
        get_nxt();
        int period = n - nxt[n];
        if(n % period == 0) printf("%d\n", n / period);
        else  puts("1");
    }
    return 0;
}