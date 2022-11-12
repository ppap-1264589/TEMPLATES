struct nCk{
    static const int maxc = 1e5 + 10;
    static const int MOD = 1e9 + 7;
    int f[maxc << 1]; //factorial
    int inv[maxc << 1]; //inverse
    int fi[maxc << 1]; //inverse factorial
    int n;

    void precompute(int n){
        f[0] = 1;
        up(i,1,n) f[i] = 1ll*f[i-1]*i % MOD;
        inv[1] = 1;
        fi[1] = 1;
        up(i,2,n){
            inv[i] = MOD - 1ll*MOD/i * inv[MOD % i] % MOD;
            fi[i] = 1ll*fi[i-1]*inv[i] % MOD;
        }
    }

    int C(int n, int k){
        if (n == 0 || k == 0) return 1;
        if (k == n) return 1;
        return 1ll*f[n] * fi[k] % MOD * fi[n-k] % MOD;
    }
} my_NCK;