// 珂朵莉树
// 区间赋值 且数据随机（或者操作种类有限）时使用
struct ODT {
    const int n;
    map<int, int> mp;
    ODT(int n) : n(n) { mp[-1] = 0; // mp[0] = 0, mp[n] = -1;}
    void split(int x) {
        auto it = prev(mp.upper_bound(x)); //找到左端点小于等于x的区间
        mp[x] = it->second; //设立新的区间，并将上一个区间储存的值复制给本区间。
    }
    void assign(int l, int r, int v) { // 注意，这里的r是区间右端点+1
        split(l);
        split(r);
        auto it = mp.find(l);
        while (it->first != r) {
            // 一般在此数可以同时完成相关的更新操作
            // 若重写一个update或者query
            // 与assign一致，就是把下一行换成 it = next(it);
            it = mp.erase(it);
        }
        mp[l] = v;
    }
};