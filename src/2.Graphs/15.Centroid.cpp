function<void(int, int)> dfs2 = [&](int v, int p){
    int mx = 0;
    for(auto u: g[v]){
        if(u == p || vis[u]) continue;
        mx = max(mx, sbt[u]);
    }
    mx = max(mx, n - sbt[v]);
    if(mx <= n / 2){
        centroid = v;
    }
    for(auto u: g[v]){
        if(u == p || vis[u]) continue;
        dfs2(u, v);
    }
};
