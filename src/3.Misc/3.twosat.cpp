struct twoSAT{
    int n, m;
    vector<vector<int>> adj, adjT;
    vector<int> val, order, comp, vis;
    twoSAT(int n) : n(n), m(2 * n), adj(2 * n), adjT(2 * n), val(n), comp(2 * n, -1), vis(2 * n) {
        order.reserve(2 * n);
    }
    void dfs1(int v){
        vis[v] = 1;
        for(auto u : adj[v]){
            if(!vis[u]) dfs1(u);
        }
        order.push_back(v);
    }
    void dfs2(int v, int cl){
        comp[v] = cl;
        for(auto u : adjT[v]){
            if(comp[u] == -1) dfs2(u, cl);
        }
    }
    void add_f(int a, bool na, int b, bool nb){
        a = (2 * a) ^ na;
        b = (2 * b) ^ nb;
        adj[a ^ 1].push_back(b);
        adj[b ^ 1].push_back(a);
        adjT[b].push_back(a ^ 1);
        adjT[a].push_back(b ^ 1);
    }
    bool solver(){
        order.clear();
        fill(vis.begin(), vis.end(), 0);
        for(int i = 0; i < m; i++){
            if(!vis[i]) dfs1(i);
        }
        comp.assign(m, -1);
        for(int i = 0, j = 0; i < m; i++){
            int v = order[m - i - 1];
            if(comp[v] == -1) dfs2(v, j++);
        }
        val.assign(n, 0);
        for(int i = 0; i < m; i += 2){
            if(comp[i] == comp[i + 1]) return false;
            val[i >> 1] = comp[i] > comp[i + 1];
        }
        return true;
    }
};