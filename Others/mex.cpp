struct Mex {
    int n;
    std::set<int> s;
    std::vector<int> cnt;
    Mex(int n) : n(n + 1), cnt(n + 2) { 
        // 这里i从0还是从1开始取决于数据
        for (int i = 0; i <= n + 1; i ++) {
            s.insert(i);
            cnt[i] = 0;
        }
    }
    int mex() {
        // assert(!s.empty());
        return *s.begin();
    }
    void insert(int x) {
        if (cnt[x]++ == 0) {
            s.erase(x);
        }
    }
    void erase(int x) {
        if (-- cnt[x] == 0) {
            s.insert(x);
        }
    }
};

// 维护一个数据结构，可插入，删除，
// 快速得到第一个不在该集合中的自然数（或从一开始的整数）