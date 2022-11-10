struct Range_Sieve{
    static const int maxn = 1e5 + 10;
    bitset<maxn> mark;
    vector<int> P;

    void range_sieve(long long l, long long r){
        mark.reset();

        for (long long i = 2; i*i <= r; i++){
            for (long long j = max(i*i, (l + i - 1)/i*i); j <= r; j += i){
                mark[j - l] = 1;
            }
        }

        if (l == 1) mark[0] = 1;
        if (l == 0) mark[0] = mark[1] = 1;
        up(i,l,r) if (!mark[i - l]) P.ep(i);
        P.clear();
    }

    void solve(int l, int r){
        range_sieve(l, r);
        for (auto x : P) cout << x << " ";
    }
} RS;