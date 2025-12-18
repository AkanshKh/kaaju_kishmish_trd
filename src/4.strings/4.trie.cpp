const int MAXB = 30;
struct node{
    int cnt;
    int t[2];
    set<int> id;
    node (){
        cnt = 0;
        t[0] = t[1] = -1;
    }
};
struct btrie{
    vector<node> trie;
    btrie() {
        trie.resize(1);
    }
    int new_node(){
        trie.push_back(node());
        return (int)trie.size() - 1;
    }
    void insert(int x, int id){
        int cur = 0;
        trie[cur].cnt ++;
        for(int i = MAXB; i >= 0; i --){
            int b = (x >> i) & 1;
            if(trie[cur].t[b] == -1){
                trie[cur].t[b] = new_node();
            }
            cur = trie[cur].t[b];
            trie[cur].cnt ++;
        }
        trie[cur].id.insert(id);    
    }
    void remove(int x, int id){
        int cur = 0;
        trie[cur].cnt --;
        for(int i = MAXB; i >= 0; i --){
            int b = (x >> i) & 1;
            cur = trie[cur].t[b];
            trie[cur].cnt --;
        }
        assert(trie[cur].id.count(id));
        trie[cur].id.erase(id);
    }
    pair<int, int> min_xor(int x){
        int cur = 0, res = 0, idx = -1;
        for(int i = MAXB; i >= 0; i --){
            int b = ((x >> i) & 1);
            if(trie[cur].t[b] != -1 && trie[trie[cur].t[b]].cnt > 0){
                cur = trie[cur].t[b];
            }
            else{
                res |= (1LL << i);
                cur = trie[cur].t[b ^ 1];
                if(cur == -1) return {res, -1};
            }
        }
        assert(!trie[cur].id.empty());
        idx = *trie[cur].id.begin();
        return {res, idx};
    }
};
auto get = [&](int x){
    // I need y such that x ^ y is maximum;
    // if x has 0 then find 1 then 0;
    // if x has 1 then find 0 then 1;
    int curr = 0;
    int ans = 0;
    for(int i = 29; i >= 0; i --){
        int bit = (x >> i) & 1;
        if(bit){
            if(trie[curr][0]){
                ans += (1 << i);
                curr = trie[curr][0];
            } else {
                curr = trie[curr][1];
            }
        } else {
            if(trie[curr][1]){
                ans += (1 << i);
                curr = trie[curr][1];
            } else {
                curr = trie[curr][0];   
            }
        }
    }
    return ans;
};