template<class T>
using min_heap = priority_queue<T,vector<T>,greater<T>>; 

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
            points.push_back(l.intersect(lines.back()));
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
