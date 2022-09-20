template<typename T>
struct matrix {
    size_t dim;
    vector<vector<T>> mtx;

    matrix(int n) : dim(n), mtx(n, vector<T>(n, 0)){}
    void I() {
        for (size_t i = 0; i < dim; i ++) {
            for (size_t j = 0; j < dim; j ++) {
                mtx[i][j] = static_cast<T>(i == j);
            }
        }
    }
    matrix operator*(const matrix &rhs) {
        assert(this->dim == rhs.dim && "Matrix dimension must be the same.");
        matrix<T> res(dim);
        for (size_t i = 0; i < dim; i ++) {
            for (size_t j = 0; j < dim; j ++) {
                for (size_t k = 0; k < dim; k ++) {
                    res.mtx[i][j] += (mtx[i][k] * rhs.mtx[k][j]) % mod;
                    res.mtx[i][j] %= mod;
                }
            }
        }
        return res;
    }

    matrix operator^(ll n) {
        matrix<T> res(dim);
        res.I();
        for (; n; n >>= 1) {
            if(n & 1) res = res * (*this);
            *this = *this * (*this);
        }
        return res;
    }

};