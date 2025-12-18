int dpOr[MAXN], dpAnd[MAXN], A[MAXN];
for(int i = 0; i < n; i ++){
    dpOr[A[i]] ++, dpAnd[A[i]] ++;
}
for(int bit = 0; bit < 20; bit ++){
    for(int msk = 0; msk < MAXN; msk ++){
        if((msk >> bit) & 1){
            dpOr[msk] += dpOr[msk ^ (1 << bit)];
        }
        else{
            dpAnd[msk] += dpAnd[msk | (1 << bit)];
        }
    }
}
