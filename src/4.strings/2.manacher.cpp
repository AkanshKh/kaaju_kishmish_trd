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