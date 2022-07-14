// 容斥原理
// 给定素数集合A(大小为k), 求[L, R]中素数集合的任意元素的倍数的个数
// 1<=L<=R<=10^18,1<=k<=20,2<=ai<=100
#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main() {
	ll l, r, k, f[25];
	cin >> l >> r >> k;
	for (int i = 0; i < k; i++) cin >> f[i];

	ll ans = 0;

	for (int i = 1; i < 1 << k; i ++) {// 枚举集合中全部的非空子集
		ll cnt = 0, a = r, b = l - 1;  // cnt用来表示所取的数的个数
		for (int j = 0; j < k; j ++) {
			if(i >> j & 1) {
				cnt++;
				a /= f[j], b /= f[j];
			}
		}
		if(cnt & 1) ans += (a - b);
		else ans -= (a - b);
	}
	cout << ans << endl;
	return 0;
}
