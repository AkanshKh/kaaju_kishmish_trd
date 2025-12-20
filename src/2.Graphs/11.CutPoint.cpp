vll g[NUM];
bool vis[NUM];
ll in[NUM];
ll low[NUM];
int timer = 0;

void CutPoints(ll src, ll parent = -1)
{
    vis[src] = true;
    in[src] = low[src] = timer;
    timer++;
    int children = 0;
    for (auto child : g[src])
    {
        if (child == parent)
            continue;
        if (vis[child])
        {
            low[src] = min(low[src], in[child]);
        }
        else
        {
            CutPoints(child, src);
            low[src] = min(low[src], low[child]);
            if (low[child] >= in[src] && parent!=-1)
            {
                // Src is a cut point! 
                // CAUTION: Might get called multiple times due to satisfiablity of multiple children
            }
            children++;
        }
    }
    if (parent==-1 && children>1){
        // Root is a cut point!
        // used children instead of size of adj bcoz we dont use back edges
    }
}
