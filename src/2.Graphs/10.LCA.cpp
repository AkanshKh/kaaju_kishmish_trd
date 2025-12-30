// LCA and Binary Lifting
void dfs(int v, int p){
    up[0][v] = p;
    for(int i = 1; i < 20; i ++){
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for(auto x : g[v]){
        if(x == p) continue;
        dst[x] = dst[v] + 1;
        dfs(x, v);
    }
}
auto lca = [&](int x, int y){
    if(dst[x] < dst[y]) swap(x, y);
    for(int i = 19; i >= 0; i --){
        if(dst[up[i][x]] >= dst[y]){
            x = up[i][x];
        }
    }
    if(x == y) return x;
    for(int i = 19; i >= 0; i --){
        if(up[i][x] != up[i][y]){
            x = up[i][x];
            y = up[i][y];
        }
    }
    return up[0][x];
};
 