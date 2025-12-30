// ans[i] = j means ith worker is assigned jth task
// O(n^3) time complexity
// It finds the assignment where the sum of costs is the lowest possible value.
void hungarian(vector<vector<long double>> &a, vll &ans){
    ll n = a.size();
    vector<ld> u(n + 1, 0), v(n + 1, 0);
    vll p(n + 1, 0), way(n + 1, 0);
    for (ll i = 1; i <= n; ++i) {
        vector<ld> minv(n + 1, INF);
        vector<bool> used(n + 1, false);
        ll j0 = 0;
        p[0] = i;
        do{
            used[j0] = true;
            ll i0 = p[j0], j1;
            long double delta = LDBL_MAX;
            for (ll j = 1; j <= n; ++j) {
                if (!used[j]) {
                    long double cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j]){
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta){
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (ll j = 0; j <= n; ++j){
                if(used[j]){
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);
        do{
            ll j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    for (ll j = 1; j <= n; ++j)
        ans[p[j] - 1] = j - 1;
}
