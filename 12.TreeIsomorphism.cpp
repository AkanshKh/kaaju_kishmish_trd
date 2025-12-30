class Tree {
public:
    vector<vector<int>> adj;
    vector<int> centroid;
    vector<int> sub;
    vector<int> id;
    vector<int64_t> powr;

    void dfs(int curNode, int prevNode) {
        sub[curNode] = 1;
        bool is_centroid = true;
        vector<pair<int, int>> nodes;
        for (int v : adj[curNode]) {
            if (v != prevNode) {
                dfs(v, curNode);
                sub[curNode] += sub[v];
                if (sub[v] > (int)adj.size() / 2) {
                    is_centroid = false;
                }
                nodes.emplace_back(id[v], v);
            }
        }
        // Canonical ordering: sort children by their hash
        sort(nodes.begin(), nodes.end());
        
        id[curNode] = 1;
        for (auto& p : nodes) {
            // Polynomial hash combination
            id[curNode] = ((powr[sub[p.second] + 1] * id[curNode]) % MOD + id[p.second]) % MOD;
        }
        id[curNode] *= 2;
        id[curNode] %= MOD;
        
        // Check "parent" component size for centroid definition
        if ((int)adj.size() - sub[curNode] > (int)adj.size() / 2) {
            is_centroid = false;
        }
        if (is_centroid) {
            centroid.push_back(curNode);
        }
    }

    vector<int> getCentroids() {
        // Clear previous runs if any
        centroid.clear();
        dfs(0, -1);
        return centroid;
    }

    // Computes hash for a specific rooting
    int getHash(int root) {
        dfs(root, -1); 
        return id[root];
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    Tree(int n) {
        adj.resize(n);
        sub.resize(n);
        id.resize(n);
        powr.resize(n + 1);
        powr[0] = 1;
        for (int i = 1; i <= n; i++) {
            powr[i] = (2 * powr[i - 1]) % MOD;
        }
    }
};

int main() {
    // Example: Two trees that look different but are structurally the same
    // Tree 1: 0-1, 1-2
    Tree t1(3);
    t1.add_edge(0, 1);
    t1.add_edge(1, 2);

    // Tree 2: 1-0, 0-2 (Same line graph, just labeled differently)
    Tree t2(3);
    t2.add_edge(1, 0);
    t2.add_edge(0, 2);

    // Step 1: Find centroids for both trees
    // This allows us to find a "Canonical Root"
    vector<int> c1 = t1.getCentroids();
    vector<int> c2 = t2.getCentroids();

    bool isomorphic = false;

    // Step 2: Compare hashes rooted at centroids
    // A tree can have up to 2 centroids. We must check all combinations.
    for (int root1 : c1) {
        for (int root2 : c2) {
            if (t1.getHash(root1) == t2.getHash(root2)) {
                isomorphic = true;
            }
        }
    }

    if (isomorphic)
        cout << "The trees are Isomorphic!" << endl;
    else
        cout << "The trees are Different." << endl;

    return 0;
}
