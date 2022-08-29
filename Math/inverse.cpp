ll qpow(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll inv(ll x) { return qpow(x, mod - 2); }

const int N = 1e6 + 10;
// 线性递推求逆元 [1, n]的所有数关于p的逆元
int inv[N];
void init_inv () {
    int n, p;
    cin >> n >> p;
    inv[0] = 0, inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (ll)(p - p / i) * inv[p % i] % p;//为了保证大于零加了个p

    return 0;
}