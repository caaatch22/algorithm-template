void GospersHack(int k, int n) {
    int cur = (1 << k) - 1;
    int limit = (1 << n);
    while (cur < limit) {
        // do something
        int lb = cur & -cur;
        int r = cur + lb;
        cur = ((r ^ cur) >> __builtin_ctz(lb) + 2) | r;
        // 或：cur = (((r ^ cur) >> 2) / lb) | r;
    }
}