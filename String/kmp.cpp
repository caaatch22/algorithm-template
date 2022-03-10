//poj2406
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;
char s[N];
int nxt[N], n;

void get_nxt()
{
    nxt[1] = 0;
    for (int i = 2, j = 0; i <= n; i ++)
    {
        while(j && s[i] != s[j + 1]) j = nxt[j];
        if(s[i] == s[j + 1]) j++;
        nxt[i] = j;
    }
}

int main()
{
    while(~scanf("%s", s + 1))
    {
        if(s[1] == '.')  break;
        n = strlen(s + 1);
        get_nxt();
        int period = n - nxt[n];
        if(n % period == 0) printf("%d\n", n / period);
        else  puts("1");
    }

    return 0;
}