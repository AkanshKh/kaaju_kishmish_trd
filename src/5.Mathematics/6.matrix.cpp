template<typename T>
struct Matrix{
    vector<vector<T>> mat;
    int n, m;
    Matrix() {}
    Matrix(int _n, int _m, bool ident = false) {
        n = _n; m = _m;
        mat.assign(n, vector<T>(m, 0));
        if (ident) {
            for (int i = 0; i < n; i++)
                mat[i][i] = 1;
        }
    }
    Matrix(const vector<vector<T>> &v) {
        n = v.size();
        m = v[0].size();
        mat = v;
    }
    Matrix operator*(const Matrix &b) const {
        Matrix res(n, b.m);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                if (mat[i][k].val == 0) continue;
                for (int j = 0; j < b.m; j++) {
                    res.mat[i][j] += mat[i][k] * b.mat[k][j];
                }
            }
        }
        return res;
    }
};
template<typename T>
Matrix<T> mat_pow(Matrix<T> a, long long p) {
    Matrix<T> res(a.n, a.n, true);
    while (p) {
        if (p & 1) res = res * a;
        a = a * a;
        p >>= 1;
    }
    return res;
}
