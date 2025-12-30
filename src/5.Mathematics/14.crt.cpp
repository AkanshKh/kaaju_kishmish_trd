int extGcd(int a, int b, int &x, int &y){
    if(b == 0){
        x = 1; y = 0;
        return a;
    }
    int x1, y1;
    int d = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}
int modinv(int a, int m){
    int x, y;
    int g = extGcd(a, m, x, y);
    int inv = (x % m + m) % m;
    return inv;
}
// solves the two congruences and returns the minimum non-negative solution
int get(int a, int b, int c, int d, int n){
    // ax = -b mod n -> ax - kn = -b -> gcd(a, n) | b
    // cx = -d mod n
    int g1 = gcd(a, n);
    if((-b) % g1 != 0) return -1;
    int m1 = n / g1;
    int r1 = ((-b / g1) % m1 + m1) % m1;
    int x1 = (modinv(a / g1, m1) * r1) % m1;

    int g2 = gcd(c, n);
    if((-d) % g2 != 0) return -1;
    int m2 = n / g2;
    int r2 = ((-d / g2) % m2 + m2) % m2;
    int x2 = (modinv(c / g2, m2) * r2) % m2;

    // x = x1 mod m1 and x = x2 mod m2
    int g = gcd(m1, m2);
    if((x2 - x1) % g != 0) return -1;
    int M = (m1 / g) * m2;
    int inv = modinv(m1 / g, m2 / g);
    int ans = (x1 + (((x2 - x1) / g * inv) % (m2 / g)) * m1) % M;
    ans = (ans + M) % M;
    return ans;
}
