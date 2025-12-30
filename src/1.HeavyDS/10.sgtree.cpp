struct SegTree {
    int n;
    vector<int> tree;
    SegTree(int n) : n(n), tree(4 * n) {}
    void build(int node, int l, int r, const vector<int>& a) {
        if (l == r) {
            tree[node] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(node << 1, l, mid, a);
        build(node << 1 | 1, mid + 1, r, a);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }
    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (idx <= mid)
            update(node << 1, l, mid, idx, val);
        else
            update(node << 1 | 1, mid + 1, r, idx, val);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }
    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return tree[node];
        int mid = (l + r) >> 1;
        return query(node << 1, l, mid, ql, qr)
             + query(node << 1 | 1, mid + 1, r, ql, qr);
    }
};
