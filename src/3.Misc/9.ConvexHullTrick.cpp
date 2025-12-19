template<class T>
using min_heap = priority_queue<T,vector<T>,greater<T>>; 
// When lines are added in increasing order of slopes
// Queries minimum
struct CHT {
    struct Line {
        int m, c;
        Line () {}
        Line (int _m, int _c) : m(_m), c(_c) {}

        double intersect(const Line &other) const {
            return (double)(other.c - c) / (m - other.m);
        }

        int operator()(int x) const {
            return m * x + c;
        }   
    };
    vector<double> points;
    vector<Line> lines;
    void init(Line l){
        points.push_back(-inf);
        lines.push_back(l);
    }
    void add_line(Line l){
        while(lines.size() >= 2 && l.intersect(lines[lines.size() - 2]) <= points.back()){
            points.pop_back();
            lines.pop_back();
        }
        if(!lines.empty()){
            points.push_back(l.intersect( lines.back()));
        } 
        if(!lines.empty() && lines.back().m == l.m){
            if(lines.back().c >= l.c) return;
            lines.pop_back();
            points.pop_back();
        }
        lines.push_back(l);
    }
    int query(int x){
        int idx = upper_bound(al(points), x) - points.begin() - 1;
        return lines[idx](x);
    }
};
void solve(){
    int n, c; cin>>n>>c;
    vector<int> a(n + 1), dp(n + 1);
    for(int i = 1; i <= n; i ++){
        cin>>a[i];
    }

    CHT cht;
    cht.init(CHT::Line(-2 * a[1], a[1] * a[1]));
    for(int i = 2; i <= n; i ++){
        dp[i] = cht.query(a[i]) + a[i] * a[i] + c;
        cht.add_line(CHT::Line(-2 * a[i], dp[i] + a[i] * a[i]));
    }
    cout<<dp[n]<<endl;
}

// Anyhow works, Queries Maximum
struct Line {
    mutable int k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(int x) const { return p < x; }
};

struct CHT : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    int div(int a, int b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(int k, int m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    int query(int x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
