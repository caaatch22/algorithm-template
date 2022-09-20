// lead前导0， lim是否到限制
int a[N], dp[N][N];
int dfs(int pos, int pre, bool lead, bool limit) {
    if (!pos) {
        // 边界条件
    }
    if (!limit && !lead && dp[pos][pre] != -1) return dp[pos][pre];
    int res = 0, up = limit ? a[pos] : 无限制位;
    for (int i = 0; i <= up; i ++) {
        if (不合法条件) continue;
        res += dfs(pos - 1, 未定参数, lead && !i, limit && i == up);
    }
    return limit ? res : (lead ? res : dp[pos][sum] = res);
}

int cal(int x) {
    // 一般dp初始化成-1， len = 0;
    memset(dp, -1, sizeof dp);
    len = 0;
    while (x) a[++ len] = x % 进制, x /= 进制;
    return dfs(len, 未定参数, 1, 1);
}

int main() {
    cin >> l >> r;
    cout << cal(r) - cal(l - 1) << endl;
}
