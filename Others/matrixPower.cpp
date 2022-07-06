#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int mod = 1e9 + 7;

struct Matrix {
    ll a[3][3];
    Matrix() { memset(a, 0, sizeof a); }

    Matrix operator*(const Matrix &rhs) const {
        Matrix res;
        for (int i = 1; i <= 2; ++i)
            for (int j = 1; j <= 2; ++ j)
                for (int k = 1; k <= 2; ++k)
                    res.a[i][j] = (res.a[i][j] + a[i][k] * rhs.a[k][j]) % mod;
        return res;
    }
} ans, base;

void init() {
    base.a[1][1] = base.a[1][2] = base.a[2][1] = 1;
    ans.a[1][1] = ans.a[1][2] = 1;
}

void qpow(ll b) {
    while(b) {
        if(b & 1) ans = ans * base;
        base = base * base;
        b >>= 1;
    }
}

ll n;

int main() {

    cin >> n;
    if(n <= 2) 
        puts("1");
    else {
        init();
        qpow(n - 2);
        cout << ans.a[1][1] % mod;
    }
    return 0;
}