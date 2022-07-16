using ull = unsigned long long;
const int N = 1e5 + 10;
char s[N];
int n;

namespace Hash
{ //字符串s定义在全局，且下标从1开始
ull h[N], p[N], ht[N];
const int base = 131;

void build() {
    p[0] = 1; //注意n是s的长度
    for (int i = 1; i <= n; i++) {
        p[i] = p[i - 1] * base;
        h[i] = h[i - 1] * base + s[i] - '0';
    }
    // 对于另一个字符串 t， 需要char t[N], ht[N], m=|t|
    // for (int i = 1; i <= m; i++)
    //     ht[i] = ht[i - 1] * base + t[i] - '0';
}
ull get(int l, int r) { 
    // if(r < l || l > n) return 0; //根据题目需要处理边界情况
    return h[r] - h[l - 1] * p[r - l + 1]; }
};