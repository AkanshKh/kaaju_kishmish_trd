struct dsu_state{
    int v, u, rnk_v, rnk_u;
    dsu_state() {}
    dsu_state(int v, int u, int rnk_v, int rnk_u) 
        : v(v), u(u), rnk_v(rnk_v), rnk_u(rnk_u) {}
};
struct dsuRoll{
    vector<int> par, rnk;
    stack<dsu_state> st;
    int comps;
    dsuRoll() {}
    dsuRoll(int n){
        par.resize(n + 1), rnk.resize(n + 1, 0);   
        for(int i = 1; i <= n; i ++){
            par[i] = i;
            rnk[i] = 0;
        }
        comps = n;
    }
    int find(int v){
        return (v == par[v]) ? v : find(par[v]);
    }
    bool unite(int x, int y){
        x = find(x), y = find(y);
        if(x == y) return false;
        if(rnk[x] > rnk[y]) swap(x, y);
        st.push(dsu_state(x, y, rnk[x], rnk[y]));
        par[x] = y;
        if(rnk[x] == rnk[y]) rnk[y] ++;
        comps --;
        return true;
    }
    void rollback(){
        if(st.empty()) return;
        auto cur = st.top(); st.pop();
        comps ++;
        par[cur.v] = cur.v;
        par[cur.u] = cur.u;
        rnk[cur.v] = cur.rnk_v;
        rnk[cur.u] = cur.rnk_u;
    }
};

struct qry{
    int v, u; 
    bool f;
    qry() {}
    qry(int v, int u) : v(v), u(u) {}
};

struct dynCon{
    int n, sz;
    vector<vector<qry>> seg;
    dsuRoll dsu;
    dynCon(int _n, int _q) : n(_n), sz(_q) {
        dsu = dsuRoll(_n);
        seg.resize(4 * _q + 5);
    }
    void add(int idx, int st, int en, int ql, int qr, qry& q){
        if(st > qr || en < ql) return;
        if(st >= ql && en <= qr){
            seg[idx].push_back(q);
            return;
        }
        int md = (st + en) >> 1;
        add(idx << 1, st, md, ql, min(qr, md), q);
        add(idx << 1 | 1, md + 1, en, max(md + 1, ql), qr, q);
    }
    void add(int l, int r, qry q){
        add(1, 0, sz, l, r, q);
    }
    void run(int v, int l, int r, vector<int>& ans){
        for(auto &q : seg[v]) q.f = dsu.unite(q.v, q.u);
        if(l == r) { /* do something */ }
        else{
            int md = (l + r) >> 1;
            run(v << 1, l, md, ans);
            run(v << 1 | 1, md + 1, r, ans);
        }
        for(auto &q : seg[v]) if(q.f) dsu.rollback();
    }
    vector<int> solve(){
        vector<int> ans(sz + 1);
        run(1, 0, sz, ans);
        return ans;
    }
};

int n, q; 
fscanf(in, "%d %d", &n, &q);
map<pair<int, int>, int> mp;
vector<int> ans(q + 1);
dynCon dc(n, q);
for(int i = 0; i < q; i ++){
    char c; fscanf(in, " %c", &c);
    if(c == '?'){
        ans[i] = 1;
    }
    else{
        int v, u; 
        fscanf(in, "%d %d", &v, &u);
        if(v > u) swap(v, u);
        if(c == '+'){
            mp[{v, u}] = i;
        }
        else{
            dc.add(mp[{v, u}], i - 1, qry(v, u));
            mp.erase({v, u});
        }
    }
}

for(auto [p, start] : mp){
    dc.add(start, q, qry(p.first, p.second));
}

auto f = dc.solve();