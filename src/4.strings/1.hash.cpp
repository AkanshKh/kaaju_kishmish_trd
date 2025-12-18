void go_hsh(string s){
    hsh[0] = s[0];
    ppow[0] = 1;
    for(int i = 1; i < s.size(); i ++){
        hsh[i] = (((hsh[i - 1] * p) % mod) + s[i]) % mod;
        ppow[i] = (ppow[i - 1] * p) % mod;
    }
}
int get(int l, int r){
    if(!l) return hsh[r];
    return (hsh[r] - (hsh[l - 1] * ppow[r - l + 1]) % mod + mod) % mod;
}