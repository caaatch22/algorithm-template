// fac[N]记得开两倍

void init() {  // 预处理阶乘及其逆元
	fac[0] = 1;
	for (int i = 1; i < N; i++) fac[i] = (ll)fac[i - 1] * i % mod;
	ifac[N - 1] = qpow(fac[N - 1], mod - 2);
	for (int i = N - 1; i; i--) ifac[i - 1] = (ll)ifac[i] * i % mod;
}

ll C(int n, int m) {  // 组合数C(n,m)
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

ll ans = C(2 * n, n) * qpow(n + 1, mod - 2) % mod;
// or
ll ans = 1LL * (C(2 * n, n) - C(2 * n, n - 1) + mod) % mod;