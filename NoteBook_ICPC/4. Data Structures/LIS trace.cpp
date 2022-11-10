struct LIS{
    const int maxn = 1e5 + 10;
    int F[maxn];
    int B[maxn];
    int A[maxn];
    int n;
    int res = 0;

    void input(){
        cin >> n;
        up(i,1,n) cin >> a[i];
    }

    void DP(){
        up(i,1,n){
            F[i] = lower_bound(B+1, B+res+1, A[i]) - B;
            res = max(res, F[i]);
            B[F[i]] = A[i];
        }
        cout << res;
    }

    void trace(int len){
        vector<int> p;
        down(i,n,1){
            if (F[i] == len){
                p.push_back(A[i]);
                --len;
            }
        }
        reverse(p.begin(), p.end());
        for (auto x : p) cout << x << " ";
    }
} my_LIS;
