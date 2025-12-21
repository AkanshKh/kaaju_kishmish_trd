void solve()
{
    ll p, f;
    cin >> p >> f;
    vector<vll> adj(p);
    vll deg(p, 0);
    rep(i, f)
    {
        ll a, b;
        cin >> a >> b;
        --a;
        --b;
        adj[a].pb(b);
        adj[b].pb(a);
        deg[a]++;
        deg[b]++;
    }
 
    vector<bitset<NUM + 1>> mat(p);
    rep(v, p)
    {
        for (auto u : adj[v])
            mat[v].set(u);
        if (deg[v] & 1)
            mat[v].set(v);
        else
            mat[v].set(p);
    }
 
    // The below code is taken from internet (Gaussian Elimination in GF(2))
    ll row = 0;
    for (ll col = 0; col < p && row < p; ++col)
    {
        ll sel = -1;
        for (ll r = row; r < p; ++r)
        {
            if (mat[r].test(col))
            {
                sel = r;
                break;
            }
        }
        if (sel == -1)
            continue;
        if (sel != row)
            swap(mat[sel], mat[row]);
        for (ll r = 0; r < p; ++r)
        {
            if (r != row && mat[r].test(col))
            {
                mat[r] ^= mat[row];
            }
        }
        ++row;
    }
 
    for (ll r = 0; r < p; ++r)
    {
        bool allzero = true;
        for (ll c = 0; c < p; ++c)
            if (mat[r].test(c))
            {
                allzero = false;
                break;
            }
        if (allzero && mat[r].test(p))
        {
            cout << 'N' << endl;
            return;
        }
    }
 
    cout << 'Y' << endl;
}