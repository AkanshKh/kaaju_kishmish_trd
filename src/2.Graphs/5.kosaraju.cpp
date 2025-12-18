vector<int> g[n + 1], rg[n + 1];
for(auto [x, y, w] : edgs){
    g[x].push_back(y);
    rg[y].push_back(x);
}
vector<int> order;
vector<int> vis(n + 1, -1);
function<void(int)> dfs = [&](int v){
    vis[v] = 1;
    for(auto x : g[v]){
        if(vis[x] == -1) dfs(x);
    }
    order.push_back(v);
};
for(int i = 1; i <= n; i ++) if(vis[i] == -1) dfs(i);
reverse(al(order));
int idx = 1;
for(int i = 1; i <= n; i ++) vis[i] = -1;
function<void(int, vector<int>&)> dfs2 = [&](int v, vector<int>& cmp){
    vis[v] = 1;
    for(auto x : rg[v]){
        if(vis[x] == -1) dfs2(x, cmp);
    }
    cmp.push_back(v);
};
vector<int> dag(n + 1, -1);
for(auto x : order){
    if(vis[x] == -1){
        vector<int> cmp;
        dfs2(x, cmp);
        for(auto y : cmp) dag[y] = idx;
        idx ++; 
    }
}
set<int> ng[idx], idg(idx, 0);
for(int i = 1; i <= n; i ++){
    for(auto x : g[i]){
        if(dag[x] != dag[i]){
            ng[dag[i]].insert(dag[x]);
        }
    }
}
for(int i = 1; i < idx; i ++){
    for(auto x : ng[i]) idg[x] ++;
}
queue<int> q;
vector<int> dp(idx, 0);
for(int i = 1; i < idx; i ++){
    if(idg[i] == 0){
        q.push(i);
        dp[i] = 1;
    }
}
while(!q.empty()){
    auto v = q.front(); q.pop();
    for(auto x : ng[v]){
        idg[x] --;
        dp[x] = max(dp[x], dp[v] + 1);
        if(!idg[x]) q.push(x);
    }
}