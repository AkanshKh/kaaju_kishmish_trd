int low[MAXN];      // smallest prime factor
int phi[MAXN];      // Euler Totient Function
int mu[MAXN];       // Mobius function
vector<int> primes;
void sieve() {
    for (int i = 1; i < MAXN; i++) {
        phi[i] = i;
        mu[i] = 1;
    }
    for (int i = 2; i < MAXN; i++) {
        if (low[i] == 0) {                 // i is prime
            low[i] = i;
            primes.push_back(i);
            phi[i] = i - 1;
            mu[i] = -1;

            for (int j = i; j < MAXN; j += i) {
                if (low[j] == 0) low[j] = i;
                phi[j] -= phi[j] / i;
                if ((j / i) % i == 0)
                    mu[j] = 0;
                else
                    mu[j] *= -1;
            }
        }
    }
}
