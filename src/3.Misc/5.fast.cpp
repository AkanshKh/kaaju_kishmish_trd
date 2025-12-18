namespace fast {
    char B[1 << 18], *S = B,*T = B;
    #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 18, stdin), S == T) ? 0 : *S++)
    long long read() {
        long long ret = 0; char c;
        int f = 0;
        while (c = getc(), (c != '-') && (c < '0' || c > '9'));
        for (; (c >= '0' && c <= '9') || c == '-'; c = getc()){
            if(c == '-') f = 1;
            else ret = ret * 10 + c - '0';
        }
        return f ? -ret : ret;
    }
}