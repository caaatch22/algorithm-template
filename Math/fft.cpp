#include <bits/stdc++.h>
#include <any>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++)
using namespace std;

namespace FFT {
const double PI = acos(-1);
using C = complex<double>;
vector<int> rev;
vector<C> roots{C(0, 0), C(1, 0)};
void dft(vector<C>& a) {
    int n = (int)a.size();
    if ((int)rev.size() != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; ++i) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
    }
    if ((int)roots.size() < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            C e = polar(1.0, PI / (1 << k));
            for (int i = 1 << (k - 1); i < (1 << k); ++i) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = roots[i] * e;
            }
        ++k;
        }
    }
    for (int i = 0; i < n; ++i) if (rev[i] < i) {
        swap(a[i], a[rev[i]]);
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; ++j) {
                auto u = a[i + j], v = a[i + j + k] * roots[k + j];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
}
void idft(vector<C>& a) {
  int n = (int)a.size();
  reverse(a.begin() + 1, a.end());
  dft(a);
  for (auto& x : a) x /= n;
}
} // namespace FFT


vector<int> mul(const vector<int> &A, const vector<int> &B) {
	int n = max(A.size(), B.size()), tot = max(1, n * 2 - 1);
	int sz = 1 << __lg(tot * 2 - 1);
	vector<complex<double>> C(sz);
	for (int i = 0; i < A.size(); ++i) C[i].real(A[i]);
	for (int i = 0; i < B.size(); ++i) C[i].imag(B[i]);
	FFT::dft(C);
	for (auto &x : C) x *= x;
	FFT::idft(C);
	vector<int> ans(A.size() + B.size() - 1);
	for (int i = 0; i < ans.size(); ++i) ans[i] = int(C[i].imag() / 2 + 0.2);
	return ans;
}

int main() {

	cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	vector<int> a(n + 1), b(m + 1);
	for (auto &x : a) cin >> x;
	for (auto &x : b) cin >> x;
	auto c = mul(a, b);
	for (auto &x : c) cout << x << ' ';
	cout << '\n';
    std::any a = 34;
    return 0;

}