// 1. Standard Sieve to generate primes up to sqrt(MaxR)
// MaxR = 10^12 usually, so limit = 10^6
void simpleSieve(int limit, vector<int> &primes)
{
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int p = 2; p * p <= limit; p++)
    {
        if (is_prime[p])
        {
            for (int i = p * p; i <= limit; i += p)
                is_prime[i] = false;
        }
    }

    for (int p = 2; p <= limit; p++)
    {
        if (is_prime[p])
        {
            primes.push_back(p);
        }
    }
}

// 2. Segmented Sieve for range [L, R]
vector<long long> segmentedSieve(long long L, long long R)
{
    // A. Generate small primes up to sqrt(R)
    int lim = sqrt(R);
    vector<int> small_primes;
    simpleSieve(lim, small_primes);

    // B. Create a boolean array for the range [L, R]
    // is_prime[i] corresponds to number (L + i)
    vector<bool> is_prime(R - L + 1, true);

    // C. Mark multiples of small primes
    for (int p : small_primes)
    {
        // Find the first multiple of p that is >= L
        // Formula: (L + p - 1) / p * p gives ceil(L/p) * p
        long long start = (L + p - 1) / p * p;

        // Corner case: If start is the prime itself, move to next multiple
        // (We don't want to mark the prime itself as composite)
        if (start == p)
            start += p;

        // Mark all multiples in range
        // Index conversion: number x maps to index (x - L)
        for (long long i = start; i <= R; i += p)
        {
            // Check bounds just in case (start could be > R if p > R)
            if (i >= L)
            {
                is_prime[i - L] = false;
            }
        }
    }

    // D. Collect primes
    vector<long long> primes;
    for (long long i = 0; i <= R - L; i++)
    {
        if (is_prime[i])
        {
            long long num = L + i;
            if (num > 1)
            { // 1 is not prime
                primes.push_back(num);
            }
        }
    }
    return primes;
}
