struct mint {
    int val;
    mint(long long v = 0) {
        if (v < 0) {
            v = v % N + N;
        }
        if (v >= N) {
            v %= N;
        }
        val = v;
    }
    static int mod_inv(int a, int m = N) {
        int g = m, r = a, x = 0, y = 1;
        while (r != 0) {
            int q = g / r;
            g %= r; swap(g, r);
            x -= q * y; swap(x, y);
        }
        return x < 0 ? x + m : x;
    }
    explicit operator int() const {
        return val;
    }
    mint& operator+=(const mint &other) {
        val += other.val;
        if (val >= N) val -= N;
        return *this;
    }
    mint& operator-=(const mint &other) {
        val -= other.val;
        if (val < 0) val += N;
        return *this;
    }
    typedef unsigned long long ull;
    ull fast_N(ull a, ull b, ull M = N) {
        long long ret = a * b - M * ull(1.L / M * a * b);
        return ret + M * (ret < 0) - M * (ret >= (long long)M);
    }
    mint& operator*=(const mint &other) {
        val = fast_N((ull) val, other.val);
        return *this;
    }
    mint& operator/=(const mint &other) {
        return *this *= other.inv();
    }
    friend mint operator+(const mint &a, const mint &b) { return mint(a) += b; }
    friend mint operator-(const mint &a, const mint &b) { return mint(a) -= b; }
    friend mint operator*(const mint &a, const mint &b) { return mint(a) *= b; }
    friend mint operator/(const mint &a, const mint &b) { return mint(a) /= b; }
    mint& operator++() {
        val = val == N - 1 ? 0 : val + 1;
        return *this;
    }
    mint& operator--() {
        val = val == 0 ? N - 1 : val - 1;
        return *this;
    }
    mint operator++(int32_t) { mint before = *this; ++*this; return before; }
    mint operator--(int32_t) { mint before = *this; --*this; return before; }
    mint operator-() const {
        return val == 0 ? 0 : N - val;
    }
    bool operator==(const mint &other) const { return val == other.val; }
    bool operator!=(const mint &other) const { return val != other.val; }
    mint inv() const {
        return mod_inv(val);
    }
    mint pow(long long p) const {
        assert(p >= 0);
        mint a = *this, result = 1;
 
        while (p > 0) {
            if (p & 1)
                result *= a;
 
            a *= a;
            p >>= 1;
        }
        return result;
    }
    friend ostream& operator<<(ostream &stream, const mint &m) {
        return stream << m.val;
    }
    friend istream& operator >> (istream &stream, mint &m) {
        return stream >> m.val;
    }
};
template<typename T, const int P>
class comb {
public:
    int n;
    vector<T> fac, ifac, inv, pow;
    comb(int n) : n(n), fac(n), ifac(n), inv(n), pow(n) {
        fac[0] = ifac[0] = inv[0] = pow[0] = T(1);
        for(int i = 1; i <= n; i ++){
            inv[i] = T(1) / T(i);
            fac[i] = fac[i - 1] * T(i);
            ifac[i] = ifac[i - 1] * inv[i];
            pow[i] = pow[i - 1] * T(P);
        }
    }

    T ncr(int n, int r){
        if(n < r) return T(0);
        if(n < 0 || r < 0) return T(0);
        return fac[n] * ifac[r] * ifac[n - r];
    }
};
comb<mint, 2> com(MAXN);