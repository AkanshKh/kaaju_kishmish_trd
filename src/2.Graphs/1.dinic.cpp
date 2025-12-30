template<class T>
struct Flow {
    const int n;
    struct Edge {
        int to;
        T cap;
        Edge(int to, T cap) : to(to), cap(cap) {}
    };
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
    Flow(int n) : n(n), g(n) {}
    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            const int u = que.front();
            que.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t) {
                        return true;
                    }
                    que.push(v);
                }
            }
        }
        return false;
    }
    T dfs(int u, int t, T f) {
        if (u == t) return f;
        auto r = f;
        for (int &i = cur[u]; i < (int)(g[u].size()); ++i) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, T c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    T maxFlow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }
    void get(int end){
        vector<int> path;
        cur.assign(n, 0);
        int u = 1;
        while(u != end){
            path.push_back(u);
            dbg(path)
            for (int &i = cur[u]; i < (int)(g[u].size()); ++i) {
                const int j = g[u][i];
                auto [v, c] = e[j];
                dbg(u, v, c, j)
                if (j % 2 == 0 && c == 0) {
                    e[j].cap = 1;
                    u = v;
                    break;
                }
            }
        }
        path.push_back(end);
        cout<<path.size()<<endl;
        for(int i : path) cout<<i<<" ";
        cout<<endl;
    }
};
queue<int> q;
vector<bool> vis(n + 1, false);
q.push(1);
vis[1] = true;
while(!q.empty()){
    int u = q.front(); q.pop();
    for(auto i: mf.g[u]){
        auto [v, c] = mf.e[i];
        if(c > 0 && !vis[v]){
            vis[v] = true;
            q.push(v);
        }
    }
}
for(int i = 1; i <= n; i ++){
    for(auto id : mf.g[i]){
        auto [v, c] = mf.e[id];
        if(v != s and c == 0){
            cout<<i<<" "<<v - n<<endl;
        }
    }
}