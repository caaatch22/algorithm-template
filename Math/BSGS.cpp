// find smallest non-negative $x$ s.t. $a^x = b \mod p$, or $-1$(assume $0^0 = 1$)
int babyStepGiantStep(int a, int b, int p) {
    a %= p; b %= p;
    if (p == 1 || b == 1) return 0;
    int cnt = 0, t = 1;
    for (int g = __gcd(a, p); g != 1; g = __gcd(a, p)) {
        if (b % g) return -1;
        p /= g;
        ++cnt;
        b /= g;
        t = 1LL * t * (a / g) % p;
        if (b == t) return cnt;
    }
    std::map<int, int> mp;
    int m = ceil(std::sqrt(p));
    int base = b;
    for (int i = 0; i != m; ++i) {
        mp[base] = i;
        base = 1LL * base * a % p;
    }
    base = powMod(a, m, p);
    for (int i = 1; i <= m; ++i) {
        t = 1LL * t * base % p;
        if (mp.count(t))
            return (1LL * i * m - mp[t]) % p + cnt;
    }
    return -1;
}
// https://www.luogu.com.cn/problem/P4195
