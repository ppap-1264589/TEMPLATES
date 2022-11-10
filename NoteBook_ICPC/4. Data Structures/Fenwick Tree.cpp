struct Fenwick_Tree{
    static const int maxn = 1e5 + 10;
    int F[maxn];
    int n;

    void update(int x, int val){
        for (; x <= n; x += (x & (-x))) F[x] += val;
    }

    int get(int x){
        int res = 0;
        for (; x; x -= (x & (-x))) res += F[x];
        return res;
    }

    int Lower_Prefix(int x){ // Find lowest i in prefix_sum such that prefix_sum[i] >= x
        int pos = 0; // Target pos
        int sum = 0; // Prefix sum
        for (int i = log2(n); i >= 0; i--){
            int bi = pos + (1 << i);
            if (bi <= n && sum + F[bi] < x){
                pos = bi; // liftup
                sum += F[bi];
            }
        }
        return pos+1;
    }
} BIT;