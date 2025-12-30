namespace GetPrimitve{
    vi Divisors;
    vi Divisor(lli x){vi ans;
        for(lli i=2;i*i<=x;i++){
            if(x%i==0){ans.EB(i);while(x%i==0)x/=i;}
        }
        if(x>1)ans.EB(x);return ans;
    }
    bool check(int prim,int p,vi &divs){
        for(auto v:divs){
            if(binpow(prim,(p-1)/v,p)==1)return 0;
        }return 1;
    }
    int getRoot(int p){
        int ans=2;vi divs=Divisor(p-1);
        while(!check(ans,p,divs))ans++;
        return ans;
    }
};
//7340033       5
//998244353     3
const lli MAXB = 1 << 21;
using polybase = lli;
polybase A[MAXB], B[MAXB], C[MAXB];
template<lli NTTMOD,lli PRIMITIVE_ROOT> struct POLYMUL{
    lli modInv(lli a) { return a <= 1 ? a : (long long) (NTTMOD - NTTMOD / a) * modInv(NTTMOD % a) % NTTMOD; }
    void NTT(polybase P[], lli n, lli oper) {
      for(int i=1,j=0;i<n-1;i++){
        for(int s=n;j^=s>>=1,~j&s;);
        if(i<j)swap(P[i],P[j]);
      }
      for(int d=0;(1<<d)<n;d++){
        int m=1<<d,m2=m*2;
        lli unit_p0=::binpow(PRIMITIVE_ROOT,(NTTMOD-1)/m2,NTTMOD);
        if(oper<0)unit_p0=modInv(unit_p0);
        for(int i=0;i<n;i+= m2) {
          polybase unit = 1;
          for (int j = 0; j < m; j++) {
            polybase &P1 = P[i + j + m], &P2 = P[i + j];
            polybase t = unit * P1 % NTTMOD;
            P1 = (P2 - t + NTTMOD) % NTTMOD; P2 = (P2 + t) % NTTMOD;
            unit = unit * unit_p0 % NTTMOD;
          }
        }
      }
    }
    vector<polybase> mul(const vector<polybase> &a, const vector<polybase> &b) {
        vector<polybase> ret(max(0LL, (lli) a.size() + (lli) b.size() - 1), 0);
        int len = 1; while (len < (lli)ret.size()) len <<= 1;
        for (int i = 0; i < len; i++) A[i] = i < (int)a.size() ? a[i] : 0;
        for (int i = 0; i < len; i++) B[i] = i < (int)b.size() ? b[i] : 0;
        NTT(A, len, 1); NTT(B, len, 1);
        for (lli i = 0; i < len; i++) C[i] = (polybase) A[i] * B[i] % NTTMOD;
        NTT(C, len, -1); for (lli i = 0, inv = modInv(len); i < (lli)ret.size(); i++) ret[i] = (long long) C[i] * inv % NTTMOD;
        return ret;
    }
    vi binpow(vi b,lli p){
        vi ans=vi(1,1);
        for(;p;p>>=1){
            if(p&1)ans=mul(ans,b);
            b=mul(b,b);
        }
        return ans;
    }
    vi calc(vi &arr,int l,int r){
        if(l==r){
            //base case;
            return {};
        }
        int mid=(l+r)>>1;
        vi x=calc(arr,l,mid),y=calc(arr,mid+1,r);
        return mul(x,y);
    }
};
POLYMUL<998244353,3> ntt;


lli phi(lli x){// will be a power of 2 mostly.
    if(x==1)return 1;
    else return x/2;
}

vi arr[20];
void solve(){
    lli n,k,q;
    arr[1].assign(100001,0);
    cin>>n>>k;
    vi divs;
    lli cur=1;
    while(n%cur==0){
        divs.EB(cur);
        cur*=2;
    }
    fr(i,k){
        lli x;cin>>x;arr[1][x]++;
    }   
    rep(i,2,19){
        arr[i]=ntt.mul(arr[i-1],arr[i-1]);
        if(arr[i].size()>100001)arr[i].resize(100001);
    }
    sort(all(divs));
    cin>>q;
    fr(_i,q){
        lli S;cin>>S;
        lli ans=0;
        for(int i=0;i<divs.size();i++){
            if(S%(n/divs[i])!=0)continue;
            ans=(ans+arr[i+1][S/(n/divs[i])]*phi(n/divs[i]))%MOD;
        }
        ans=ans*binpow(n,MOD-2,MOD)%MOD;
        cout<<ans<<endl;
    }
}       

// youKnowWho's FFT
using cd = complex<double>;
const double PI = acos(-1);
 
void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (cd & x : a) x /= n;
    }
}
vector<int> multiply(vector<int> const& a, int n)
{
    vector<cd> fa(n);
    for (int i = 0; i < (int)a.size(); i++) {
        fa[i] = a[i];
    }
    for(int i = a.size(); i < n; i ++){
        fa[i] = 0;
    }
    fft(fa, false);
    for(int i = 0; i < n; i ++){
        fa[i] *= fa[i];
    }
    fft(fa, true);

    vector<int> res(n);
    for(int i = 0; i < n; i ++){
        res[i] = round(fa[i].real());
    }
    return res;
}

vector<int> p(MAXN);
void solve(){
    int n; cin>>n;
    int mx = 1;
    vector<int> s(n + 1);
    for(int i = 1; i <= n; i ++){
        cin>>s[i];
        mx = max(mx, s[i]);
    }
    mx += 1000;
    for(int i = 1; i <= n; i ++){
        p[s[i]] = 1;
    }

    n = 1;
    while(n <= MAXN){
        n <<= 1;
    }
    vector<int> res = multiply(p, n);
    // dbg(res);

    int c = 0;
    for(int i = 2; i <= 2 * mx; i += 2){
        int md = i / 2;
        if(p[md]){
            c += (res[i] - 1) / 2;
        }
    }
    cout<<c<<endl;
}
