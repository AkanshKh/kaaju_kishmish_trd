vll g[NUM];
ll in[NUM], low[NUM], vis[NUM];
int timer = 0;
void CutPoints(ll src, ll parent = -1){
    vis[src] = true;
    in[src] = low[src] = timer;
    timer++;
    int children = 0;
    for (auto child : g[src]) {
        if (child == parent)
            continue;
        if (vis[child]){
            low[src] = min(low[src], in[child]);
        } else{
            CutPoints(child, src);
            low[src] = min(low[src], low[child]);
            if (low[child] >= in[src] && parent!=-1)
            {
                // Src is a cut point! 
            }
            children++;
        }
    }
    if (parent==-1 && children>1){
        // Root is a cut point!
    }
}
