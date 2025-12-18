struct PST{
    struct Node{
        int sum = 0;
        int l = 0, r = 0;
    };
    const int n;
    vector<Node> tree;
    int timer = 1;
    PST(int n, int mx_nodes) : n(n), tree(mx_nodes) {}
    Node merge(int l, int r){
        return Node({tree[l].sum + tree[r].sum, l, r});
    }
    int build(int st, int en, const vector<int> &init){
        if(st == en){
            tree[timer] = Node({init[st], 0, 0});
            return timer ++;
        }
        int md = (st + en) >> 1;
        tree[timer] = merge(build(st, md, init), build(md + 1, en, init));
        return timer ++;
    }
    int update(int root, int idx, int val, int st, int en){
        if(st == en){
            tree[timer] = Node({val, 0, 0});
            return timer ++;
        }
        int md = (st + en) >> 1;
        if(idx <= md){
            tree[timer] = merge(update(tree[root].l, idx, val, st, md), tree[root].r);
        }
        else{
            tree[timer] = merge(tree[root].l, update(tree[root].r, idx, val, md + 1, en));
        }
        return timer ++;
    }
    int query(int root, int l, int r, int st, int en){
        if(r < st || en < l) return 0;
        if(l <= st && en <= r) return tree[root].sum;
        int md = (st + en) >> 1;
        return query(tree[root].l, l, r, st, md) + query(tree[root].r, l, r, md + 1, en);
    }
    int build(const vector<int> &init){
        return build(0, n - 1, init);
    }
    int update(int root, int idx, int val){
        return update(root, idx, val, 0, n - 1);
    }
    int query(int root, int l, int r){
        return query(root, l, r, 0, n - 1);
    }
};