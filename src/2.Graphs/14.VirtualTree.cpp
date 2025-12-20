const int MAXN = 200005;

// --- PREREQUISITES (LCA & DFS Times) ---
vector<int> adj[MAXN];
int tin[MAXN], tout[MAXN], timer;
int up[MAXN][20], depth[MAXN];

void dfs_lca(int u, int p, int d) {
    tin[u] = ++timer;
    depth[u] = d;
    up[u][0] = p;
    for (int i = 1; i < 20; i++)
        up[u][i] = up[up[u][i-1]][i-1];
    
    for (int v : adj[u]) {
        if (v != p) dfs_lca(v, u, d + 1);
    }
    tout[u] = timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = 19; i >= 0; i--) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

// --- VIRTUAL TREE TEMPLATE ---
vector<int> vt_adj[MAXN]; // Adjacency list for Virtual Tree

// Sorts nodes by DFS entry time (Critical for construction)
bool compare_tin(int a, int b) {
    return tin[a] < tin[b];
}

void build_virtual_tree(vector<int>& nodes) {
    // 1. Sort by DFS entry time
    sort(nodes.begin(), nodes.end(), compare_tin);

    // 2. Add LCAs of adjacent sorted nodes to the set
    // This guarantees all necessary connecting nodes are present
    int k = nodes.size();
    for (int i = 0; i < k - 1; i++) {
        nodes.push_back(lca(nodes[i], nodes[i+1]));
    }

    // 3. Sort again and remove duplicates
    sort(nodes.begin(), nodes.end(), compare_tin);
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

    // 4. Build edges using a stack
    // Clear previous virtual tree edges for these specific nodes
    for (int u : nodes) vt_adj[u].clear();

    vector<int> stack;
    stack.push_back(nodes[0]);

    for (int i = 1; i < nodes.size(); i++) {
        int u = nodes[i];
        // Pop stack while the top is NOT an ancestor of u
        // (This means we finished the subtree of stack.back())
        while (stack.size() > 1 && !is_ancestor(stack.back(), u)) {
            stack.pop_back();
        }
        // Add edge from the current direct ancestor to u
        // Note: The graph is directed downwards usually, or undirected depending on need
        vt_adj[stack.back()].push_back(u);
        vt_adj[u].push_back(stack.back()); // Add this if undirected
        
        stack.push_back(u);
    }
}
