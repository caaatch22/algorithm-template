// Returns the number of 1-bits in x.
int __builtin_popcount(unsigned int x);
int __builtin_popcountll(unsigned long long x);

// Returns the number of trailing 0 (undefined when x == 0)
int __builtin_ctz(unsigned int x);
int __builtin_ctzll(unsigned long long x);

// Returns log_2(x)
int __lg(int x);

int __gcd(int x, int y);
