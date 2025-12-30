Given two arrays $A$ and $B$ of size $n = 2^k$, compute an array $C$ such that
\[
C[x] = \sum_{\substack{i \oplus j = x}} A[i] \cdot B[j].
\]

template <typename T>
struct FWT {

    // ===== XOR =====
    void fwt_xor(T a[], int n) {
        for (int d = 1; d < n; d <<= 1) {
            for (int i = 0; i < n; i += (d << 1)) {
                for (int j = 0; j < d; j++) {
                    T x = a[i + j];
                    T y = a[i + j + d];
                    a[i + j]     = x + y;
                    a[i + j + d] = x - y;
                }
            }
        }
    }

    void ufwt_xor(T a[], int n) {
        for (int d = 1; d < n; d <<= 1) {
            for (int i = 0; i < n; i += (d << 1)) {
                for (int j = 0; j < d; j++) {
                    T x = a[i + j];
                    T y = a[i + j + d];
                    a[i + j]     = (x + y) >> 1;
                    a[i + j + d] = (x - y) >> 1;
                }
            }
        }
    }

    // ===== AND =====
    void fwt_and(T a[], int n) {
        for (int d = 1; d < n; d <<= 1) {
            for (int i = 0; i < n; i += (d << 1)) {
                for (int j = 0; j < d; j++) {
                    a[i + j] += a[i + j + d];
                }
            }
        }
    }

    void ufwt_and(T a[], int n) {
        for (int d = 1; d < n; d <<= 1) {
            for (int i = 0; i < n; i += (d << 1)) {
                for (int j = 0; j < d; j++) {
                    a[i + j] -= a[i + j + d];
                }
            }
        }
    }

    // ===== OR =====
    void fwt_or(T a[], int n) {
        for (int d = 1; d < n; d <<= 1) {
            for (int i = 0; i < n; i += (d << 1)) {
                for (int j = 0; j < d; j++) {
                    a[i + j + d] += a[i + j];
                }
            }
        }
    }

    void ufwt_or(T a[], int n) {
        for (int d = 1; d < n; d <<= 1) {
            for (int i = 0; i < n; i += (d << 1)) {
                for (int j = 0; j < d; j++) {
                    a[i + j + d] -= a[i + j];
                }
            }
        }
    }

    // ===== CONVOLUTIONS =====
    void xor_convolution(T a[], T b[], int n) {
        fwt_xor(a, n);
        fwt_xor(b, n);
        for (int i = 0; i < n; i++) a[i] *= b[i];
        ufwt_xor(a, n);
    }

    void and_convolution(T a[], T b[], int n) {
        fwt_and(a, n);
        fwt_and(b, n);
        for (int i = 0; i < n; i++) a[i] *= b[i];
        ufwt_and(a, n);
    }

    void or_convolution(T a[], T b[], int n) {
        fwt_or(a, n);
        fwt_or(b, n);
        for (int i = 0; i < n; i++) a[i] *= b[i];
        ufwt_or(a, n);
    }
};