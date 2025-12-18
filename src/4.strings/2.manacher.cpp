// Finds all palindromic substrings in O(n) time
// Returns a vector where the ith element represents the length of the longest palindromic substring
// centered at index i (for odd-length palindromes) or between indices i and i+1 (for even-length palindromes)
vector<int> manacher_odd(string s){
    int n = s.size();
    s=('$' + s + '^');
    vector<int> ans(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i ++){
        ans[i] = max(0LL, min(r - i, ans[l + (r - i)]));
        while(s[i + ans[i]] == s[i - ans[i]]){
            ans[i] ++;
        }
        if(i + ans[i] > r){
            l = i - ans[i];
            r = i + ans[i];
        }
    }
    vector<int> res;
    // we get answer as 
    // even lengthed palindrome between i & i+1 as (ans[i+1]-1)/2
    // odd centered at i as ans[i]/2
    return vector<int>(ans.begin()+1,ans.end()-1);
}
vector<int> manacher(string s){
    string t = "";
    for(auto x : s){
        t += "#";
        t += x;
    }
    t += "#";
    // cout<<t<<endl;
    auto res = manacher_odd(t);
    return vector<int>(res.begin() + 1, res.end() - 1);   
}

Manacher.h
Description: For each position in a string, computes p[0][i] = half length
of longest even palindrome around pos i, p[1][i] = longest odd (half rounded
down).
Time: O (N)
e7ad79, 13 lines
array<vi, 2> manacher(const string& s) {
    int n = sz(s);
    array<vi,2> p = {vi(n+1), vi(n)};
    rep(z,0,2) for (int i=0,l=0,r=0; i < n; i++) {
    int t = r-i+!z;
    if (i<r) p[z][i] = min(t, p[z][l+t]);
    int L = i-p[z][i], R = i+p[z][i]-!z;
    while (L>=1 && R+1<n && s[L-1] == s[R+1])
    p[z][i]++, L--, R++;
    if (R>r) l=L, r=R;
    }
    return p;
}