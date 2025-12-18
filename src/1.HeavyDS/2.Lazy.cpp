struct Min{
    int x;
    Min(int x = inf) : x(x) {}
};

Min operator+(const Min& a, const Min& b){
    return std::min(a.x, b.x);
}

void apply(int &a, int b){
    a += b;
}

void apply(Min& a, int b){
    a.x += b;
}

// Always make a class for them and define basic overloads
template<class Node, class Lazy, class Merge = std::plus<Node>>
struct LazySegTree {
    const int _n;
    const Merge _merge;
    std::vector<Node> _segT;
    std::vector<Lazy> _lazy;
    LazySegTree(int n) : _n(n), _merge(Merge()), _segT(4 << std::__lg(n)), _lazy(4 << std::__lg(n)) {}
    LazySegTree(std::vector<Node> init) : LazySegTree(init.size()) {
        std::function<void(int, int, int)> build = [&](int node, int st, int en){
            if(en - st == 1){
                _segT[node] = init[st];
                return;
            }
            int md = (st + en) >> 1;
            build(node << 1, st, md);
            build(node << 1 | 1, md, en);
            pull(node);
        };
        build(1, 0, _n);
    }
    void pull(int node){
        _segT[node] = _merge(_segT[node << 1], _segT[node << 1 | 1]);
    }
    void apply(int node, const Lazy& lazy){
        ::apply(_segT[node], lazy);
        ::apply(_lazy[node], lazy);
    }
    void push(int node){
        apply(node << 1, _lazy[node]);
        apply(node << 1 | 1, _lazy[node]);
        _lazy[node] = Lazy();
    }
    void update(int node, int st, int en, int idx, const Node& nodeVal){
        if(en - st == 1){
            _segT[node] = nodeVal;
            return;
        }
        push(node);
        int md = (st + en) >> 1;
        if(idx < md){
            update(node << 1, st, md, idx, nodeVal);
        }
        else{
            update(node << 1 | 1, md, en, idx, nodeVal);
        }
        pull(node);
    }
    void update(int idx, const Node& nodeVal){
        update(1, 0, _n, idx, nodeVal);
    }
    Node rangeQuery(int node, int st, int en, int ql, int qr){
        if(st >= qr || en <= ql){
            return Node();
        }
        if(st >= ql && en <= qr){
            return _segT[node];
        }
        push(node);
        int md = (st + en) >> 1;
        return _merge(rangeQuery(node << 1, st, md, ql, qr), rangeQuery(node << 1 | 1, md, en, ql, qr));
    }
    Node rangeQuery(int ql, int qr){
        return rangeQuery(1, 0, _n, ql, qr);
    }
    void rangeApply(int node, int st, int en, int ql, int qr, const Lazy& lazy){
        if(st >= qr || en <= ql){
            return;
        }
        if(st >= ql && en <= qr){
            apply(node, lazy);
            return;
        }
        push(node);
        int md = (st + en) >> 1;
        rangeApply(node << 1, st, md, ql, qr, lazy);
        rangeApply(node << 1 | 1, md, en, ql, qr, lazy);
        pull(node);
    }
    void rangeApply(int ql, int qr, const Lazy& lazy){
        rangeApply(1, 0, _n, ql, qr, lazy);
    }
};

// LazySegTree<Min, int> seg(a);
// For range [i, j] use i, j + 1
