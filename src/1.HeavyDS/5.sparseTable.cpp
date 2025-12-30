int log_floor(int x){
    return x ? __builtin_clzll(1) - __builtin_clzll(x)  : -1 ;
}
template<typename T , class F = function<T(const T&,const T&)>>
struct SPARSE_TABLE{  
    int n;
    vector<vector<T>> st;
    F fun;
    SPARSE_TABLE(const vector<T> &v , const F &f) : fun(f){
        n = static_cast<int>(v.size());
        int maxN = log_floor(n) + 1;
        st.resize(maxN);
        st[0] = v;
        for(int i = 1; i < maxN; i++){
            st[i].resize(n - (1 << i) + 1);

            for(int j = 0; j + (1 << i) <= n; j++){
                st[i][j] = fun(st[i - 1][j] , st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    T get(int l, int r){
        int h = log_floor(r - l + 1);
        // works for idempotent functions only ykw
        return fun(st[h][l] , st[h][r - (1 << h) + 1]);
    }
};