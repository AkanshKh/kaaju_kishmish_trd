const ll MAXN = 1e7;
const ll MOD = 1e9 + 7;
vector<ll> fac(MAXN + 1);
vector<ll> inv(MAXN + 1);
/** Computes x^y modulo p in O(log p) time. */
ll exp(ll x, ll y, ll p){
    ll res = 1;
    x %= p;
    while (y)
    {
        if (y & 1)
        {
            res *= x;
            res %= p;
        }
        x *= x;
        x %= p;
        y >>= 1;
    }
    return res;
}
void factorial() {
    fac[0] = 1;
    for (ll i = 1; i <= MAXN; i++) {
        fac[i] = ( fac[i - 1] * i ) % MOD;
    }
}
void inverses() {
    inv[MAXN] = exp(fac[MAXN], MOD - 2, MOD);
    for (ll i = MAXN; i >= 1; i--) {
        inv[i - 1] = (inv[i] * i) % MOD;
    }
}
ll choose(int n, int r) { 
    return fac[n] * inv[r] % MOD * inv[n - r] % MOD;
}
