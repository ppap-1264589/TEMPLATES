struct HashString{
    static const int maxn = 1e5 + 10;
    const int base = 311;
    const int MOD = 1e9 + 7;
    const long long MM = 1ll*MOD*MOD;

    int n;
    long long a[maxn];
    long long hashx[maxn], hashn[maxn];
    long long D[maxn]; // Decryptor

    void create(){
        D[0] = 1;
        up(i,1,n) D[i] = (D[i-1]*base) % MOD;
        up(i,1,n) hashx[i] = (hashx[i-1]*base + a[i]) % MOD;
        down(i,n,1) hashn[i] = (hashn[i+1]*base + a[i]) % MOD;
    }

    long long getx(int u, int v){
        return (hashx[v] - hashx[u-1]*D[v-u+1] + MM) % MOD;
    }

    long long getn(int u, int v){
        return (hashn[u] - hashn[v+1]*D[v-u+1] + MM) % MOD;
    }
} HASH;
