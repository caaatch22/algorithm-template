#include <bits/stdc++.h>
using namespace std;
struct Hash {
    using ull = unsigned long long;
    const int base = 131;
    int siz;
    vector<ull> pow_base, hash_val; // or p, h due to time budget
    Hash() { }
    Hash(const string &s) {
        siz = s.size();
        pow_base.resize(siz);
        hash_val.resize(siz);
        pow_base[0] = 1;
        hash_val[0] = s[0];
        for (int i = 1; i < siz; i++){
            pow_base[i] = pow_base[i - 1] * base;
            hash_val[i] = hash_val[i - 1] * base + s[i];
        }
    }
    // 下标0开始，闭区间
    ull operator[](const array<int, 2>& range) const {
        // if(r < l || l > n) return 0; //根据题目需要处理边界情况
        auto l = range[0], r = range[1];
        if(l == 0) return hash_val[r];
        return hash_val[r] - hash_val[l - 1] * pow_base[r - l + 1];
    }

    ull get(int l, int r) {
        return this->operator[]({l, r}); 
    }
};

struct doubleHash {
    using ll = long long;
    int size;
    array<int, 2> mod = {2000000011, 2000000033}, base = {20011, 20033};
    vector<array<ll, 2>> hash, pow_base;
    doubleHash() { }
    doubleHash(const string& s) {
        size = s.size();
        hash.resize(size);
        pow_base.resize(size);
        pow_base[0][0] = pow_base[0][1] = 1;
        hash[0][0] = hash[0][1] = s[0];
        for(int i = 1; i < size; i++){
            hash[i][0] = (hash[i - 1][0] * base[0] + s[i]) % mod[0];
            hash[i][1] = (hash[i - 1][1] * base[1] + s[i]) % mod[1];
            pow_base[i][0] = pow_base[i - 1][0] * base[0] % mod[0];
            pow_base[i][1] = pow_base[i - 1][1] * base[1] % mod[1];
        }
    }
    array<ll, 2> operator[](const array<int, 2>& range) const {
        auto l = range[0], r = range[1];
        if(l == 0) return hash[r];
        return {
            (hash[r][0] - hash[l - 1][0] * pow_base[r - l + 1][0] % mod[0] + mod[0]) % mod[0],
            (hash[r][1] - hash[l - 1][1] * pow_base[r - l + 1][1] % mod[1] + mod[1]) % mod[1]};
    }
    //double hash to A hash_val
    ll get(int l, int r) {
        auto h = this->operator[]({l, r});
        return h[0] * 1000000000ll + h[1];
    }
};
int main() {}