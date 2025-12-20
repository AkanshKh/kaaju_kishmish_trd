template <typename T>
struct MergeSortTree {
    int n;
    vector<vector<T>> tree;

    // Constructor: builds the tree from input vector a
    MergeSortTree(const vector<T>& a) {
        n = a.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, a);
    }

    void build(int node, int start, int end, const vector<T>& a) {
        if (start == end) {
            tree[node] = {a[start]};
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid, a);
        build(2 * node + 1, mid + 1, end, a);
        
        // Merge two sorted vectors
        merge(tree[2 * node].begin(), tree[2 * node].end(),
              tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
              back_inserter(tree[node]));
    }

    // Internal query function for Lower Bound (smallest value >= x)
    T query_lb(int node, int start, int end, int l, int r, T x) {
        if (start > end || start > r || end < l)
            return numeric_limits<T>::max(); // Return INF
        
        if (start >= l && end <= r) {
            auto it = lower_bound(tree[node].begin(), tree[node].end(), x);
            if (it != tree[node].end())
                return *it;
            return numeric_limits<T>::max();
        }

        int mid = (start + end) / 2;
        return min(query_lb(2 * node, start, mid, l, r, x),
                   query_lb(2 * node + 1, mid + 1, end, l, r, x));
    }

    // Internal query function for Count (number of elements <= x)
    int query_count(int node, int start, int end, int l, int r, T x) {
        if (start > end || start > r || end < l)
            return 0;

        if (start >= l && end <= r) {
            // upper_bound gives first element > x, so index gives count of elements <= x
            return upper_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin();
        }

        int mid = (start + end) / 2;
        return query_count(2 * node, start, mid, l, r, x) +
               query_count(2 * node + 1, mid + 1, end, l, r, x);
    }

    // Public Interface: Find smallest number >= x in range [l, r]
    T lower_bound_val(int l, int r, T x) {
        return query_lb(1, 0, n - 1, l, r, x);
    }

    // Public Interface: Count numbers <= x in range [l, r]
    int count_less_equal(int l, int r, T x) {
        return query_count(1, 0, n - 1, l, r, x);
    }
};
