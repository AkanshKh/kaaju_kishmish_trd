int A[MAXN];
typedef pair<long long, int> pii;
 
struct Block {
    vector<pii> data;
    int L;
    int R;
    long long add;
 
    Block(int l, int r) {
        L = l;
        R = r;
        add = 0;
        for (int i = l; i <= r; i++) {
            data.push_back(pii(A[i], i));
        }
        sort(data.begin(), data.end());
    }
 
    bool inter(int ql, int qr) {
        return min(R, qr) >= max(L, ql);
    }
 
    bool covered(int ql, int qr) {
        return ql <= L && R <= qr;
    }
 
    void makeAdd(int ql, int qr, long long delta) {
        if (!inter(ql, qr))
            return;
        if (covered(ql, qr)) {
            add += delta;
            return;
        }
        for (int i = 0; i < data.size(); i++)
            if (data[i].second >= ql && data[i].second <= qr) {
                data[i].first += delta;
            }
        sort(data.begin(), data.end()); 
    }
 
    int getFirst(long long x) {
        x -= add;
        pii p = pii(x, 0);
        auto it = lower_bound(data.begin(), data.end(), p);
        if (it == data.end() || it->first != x)
            return inf;
        return it->second;
    }        
 
    int getLast(long long x) {
        x -= add;
        pii p = pii(x + 1, 0);
        auto it = lower_bound(data.begin(), data.end(), p);
        if (it == data.begin())
            return -inf;
        it--;
        if(it->first == x)
            return it->second;
        return -inf;
    }
};