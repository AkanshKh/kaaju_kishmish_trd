struct basis{
    array<int, 20> b;
    int sz = 0;
    basis(){
        b.fill(0);
        sz = 0;
    }
    void insert(int x){
        for(int i = 19; i >= 0; i --){
            if((x >> i) & 1){
                if(!b[i]){
                    b[i] = x;
                    sz ++;
                    return;
                }
                x ^= b[i];
            }
        }
    }
    bool query(int x){
        for(int i = 19; i >= 0; i --){
            if(x == 0) return true;
            if((x >> i) & 1){
                if(!b[i]) return false;
                x ^= b[i];
            }
        }
        return x == 0;
    }
};