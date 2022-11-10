struct Kadane_Trace1D{
    static const int maxn = 1e6 + 10;
    long long a[maxn];
    int n;

    void KADANE(){
        bool all_negative = 1;
        cin >> n;
        up(i,1,n) {
            cin >> a[i];
            all_negative &= (a[i] < 0);
        }
        if (all_negative){
            cout << 0 << " " << 0 << " " << 0;
            exit(0);
        }

        int l = 1;
        int r = 1;
        long long sum = 0;
        long long res = (long long)(-1e18);

        int pre = 1;
        up(i,1,n){
            sum += a[i];
            if (sum < 0){
                sum = 0;
                pre = i+1;
            }
            else if (sum > res){
                res = sum;
                l = pre;
                r = i;
            }
        }
        cout << res << " " << l << " " << r;
    }
} KAN;