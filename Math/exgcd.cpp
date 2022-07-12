//拓欧解线性同余方程 a*x=b(mod m)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int a, b, m, n;

int exgcd(int a, int b, int &x, int &y) {
    if(b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a/b * x;
    return d;
}

int main() {
    int x, y;
    cin >> n;
    while(n -- ) {
        cin >> a >> b >> m;
        int d = exgcd(a, m, x, y);  // d = gcd(a, m)s
        if(b % d != 0) puts("impossible");  //bezout定理:有解的条件，gcd(a, m) | b
        else printf("%lld\n", (ll)x * (b/d) % m);
    }
    return 0;
}