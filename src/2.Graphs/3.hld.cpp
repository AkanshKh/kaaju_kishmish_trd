struct hld {
    vector<vector<int>> g;
    vector<int> par, dpth, heavy, root, pos, subt, inv;
    vector<vector<int>> up;
    segtree seg;
    int cur_pos = 0;
    hld(int n){
        g.resize(n + 1), par.resize(n + 1), dpth.resize(n + 1);
        heavy.resize(n + 1, -1), root.resize(n + 1), pos.resize(n + 1), inv.resize(n + 1);
        subt.resize(n + 1, 1);
        up.resize(n + 1);
        for(int i = 0; i <= n; i ++){
            up[i].resize(20, 0);
        }
        seg = segtree(n + 1);
        cur_pos = 0;
    }
    void add_edge(int u, int v){
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void run(int rt){
        dfs_sz(rt, 0);
        dfs_hld(rt, rt);
    }
    int dfs_sz(int v, int p){
        int sz = 1, mx_sz = 0;
        par[v] = p;
        up[v][0] = p;
        for(int i = 1; i < 20; i ++){
            up[v][i] = up[up[v][i - 1]][i - 1];
        }
        for(auto x : g[v]){
            if(x == p) continue;
            dpth[x] = dpth[v] + 1;
            int c_sz = dfs_sz(x, v);
            sz += c_sz;
            if(c_sz > mx_sz){
                mx_sz = c_sz;
                heavy[v] = x;
            }
        }
        return subt[v] = sz;
    }
    void dfs_hld(int v, int h){
        root[v] = h;
        pos[v] = cur_pos, inv[cur_pos] = v;
        cur_pos ++;
        if(heavy[v] != -1) dfs_hld(heavy[v], h);
        for(auto x : g[v]){
            if(x == par[v] || x == heavy[v]) continue;
            dfs_hld(x, x);
        }
    }
    bool is_anc(int a, int b) {
        return pos[a] <= pos[b] && pos[b] < pos[a] + subt[a];
    }
    int kth(int v, int k) {
        for (int i = 0; i < 20; i++) {
            if (k & (1 << i)) {
                v = up[v][i];
            }
        }
        return v;
    }   
    int hehe(int v, int u) {
        // u is ancestor of v
        int dif = dpth[v] - dpth[u] - 1;
        return kth(v, dif);
    }
    mint qry(int a, int b) {
        mint res = 0;
        for (; root[a] != root[b]; b = par[root[b]]) {
            if (dpth[root[a]] > dpth[root[b]])
                swap(a, b);
            mint cur_heavy_path_max = seg.prod(pos[root[b]], pos[b] + 1).x;
            res += cur_heavy_path_max;
        }
        if (dpth[a] > dpth[b])
            swap(a, b);
        mint last_heavy_path_max = seg.prod(pos[a], pos[b] + 1).x;
        res += last_heavy_path_max;
        return res;
    }
};