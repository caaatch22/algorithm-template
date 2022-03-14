#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e6 + 10;
char s[N];

int tot = 1, last = 1;
struct state{
    int len, link;
    int ch[26];
} st[N];

ll f[N];

void extnd(int c)
{
    int p = last, np = last = ++tot;
    st[np].len = st[p].len + 1;
}

int main()
{
    cin >> s;
    for (int i = 0; s[i]; i ++)
        extend(s[i] - 'a');


    return 0;
}