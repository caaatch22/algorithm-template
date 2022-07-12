// for(int i = st;i<=ed;i++) ans += num/i
ll block(ll st, ll ed, ll num) {
	//sum(num/i i in [st,ed])
	ll L = 0, res = 0;
	ed = min(ed, num);
	for (ll i = st; i <= ed; i = L + 1) {
        L = min(ed, num / (num / i)); //该区间的最后一个数
        res += (L - i + 1) * (num / i); //区间[i,L]的num/i 都是一个值
        // res += (s(L) - s(i-1)) * (num/i); //s(i)为f(i)前缀和
    }
	return res;
} 