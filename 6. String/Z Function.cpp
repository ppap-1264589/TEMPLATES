struct Z_Function{
    static const int maxn = 3e5 + 10;
    int n;
    int a[maxn], z[maxn];

    void TinhZ(){
        z[1] = 0;
        int l = 0;
        int r = 0;
        up(i,2,n){
            int x = 0;
            if (i <= r) x = min(z[i-l+1], r-i+1);
            while (i + x <= n && a[x+1] == a[i+x]) x++;

            z[i] = x;
            if (i + x - 1 > r){
                l = i;
                r = i + x - 1;
            }
        }
    }
} ZF;
//z[i] = longest common prefix of a[] till position i