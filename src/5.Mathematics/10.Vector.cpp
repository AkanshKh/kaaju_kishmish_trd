struct vec
{
    vector<ld> x;

    vec(ll n)
    {
        x.resize(n, 0);
    }
    vec operator+(const vec &other) const
    {
        vec res(x.size());
        rep(i, x.size())
        {
            res.x[i] = x[i] + other.x[i];
        }
        return res;
    }
    vec operator-(const vec &other) const
    {
        vec res(x.size());
        rep(i, x.size())
        {
            res.x[i] = x[i] - other.x[i];
        }
        return res;
    }
    vec operator*(const ld &other) const
    {
        vec res(x.size());
        rep(i, x.size())
        {
            res.x[i] = x[i] * other;
        }
        return res;
    }
    vec operator/(const ld &other) const
    {
        vec res(x.size());
        rep(i, x.size())
        {
            res.x[i] = x[i] / other;
        }
        return res;
    }
    ld dot(const vec &other) const
    {
        ld ans = 0;
        rep(i, x.size())
        {
            ans += x[i] * other.x[i];
        }
        return ans;
    }
    ld norm_sq() const
    {
        ld ans = 0;
        rep(i, x.size())
        {
            ans += x[i] * x[i];
        }
        return ans;
    }
    ld norm() const
    {
        return sqrt(norm_sq());
    }
};

ld dist(vec &p, vec &a, vec &b)
{
    vec ab = b - a;
    vec ap = p - a;
    ld seglensq = ab.norm_sq();
    if (seglensq < 1e-12)
    {
        return ap.norm();
    }
    ld t = ap.dot(ab) / seglensq;
    if (t < 0)
        t = 0;
    if (t > 1)
        t = 1;
    vec q = a + (ab * t);
    return (q - p).norm();
}
