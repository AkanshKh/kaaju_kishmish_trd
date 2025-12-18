// Bridges
vector<int> tin(n + 1, -1), low(n + 1, -1), vis(n + 1, 0);
int clk = 0;
vector<pair<int, int>> ans;
function<void(int, int)> dfs = [&](int v, int p){
    vis[v] = 1;
    tin[v] = low[v] = clk ++;
    for(auto x : g[v]){
        if(x == p) continue;
        if(!vis[x])
            dfs(x, v);
        low[v] = min(low[v], low[x]);
        if(low[x] > tin[v]){
            ans.push_back({v, x});
        }
    }
};

for(int i = 1; i <= n; i ++){
    if(!vis[i]){
        dfs(i, -1);
    }
}

// Articulation Points
function<void(int, int)> dfs = [&](int v, int p){
    vis[v] = 1;
    tin[v] = low[v] = clk ++;
    int c = 0;
    for(auto x : g[v]){
        if(x == p) continue;
        if(vis[x]){
            low[v] = min(low[v], tin[x]);
        }
        else{
            dfs(x, v);
            low[v] = min(low[v], low[x]);
            if(low[x] >= tin[v] && p != -1){
                ans.insert(v);
            }
            c ++;
        }
    }
    if(c > 1 && p == -1){
        ans.insert(v);
    }
};

for(int i = 1; i <= n; i ++){
    if(!vis[i]){
        dfs(i, -1);
    }
}
