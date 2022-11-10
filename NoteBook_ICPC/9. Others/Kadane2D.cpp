struct Kadane_Trace2D{
    static const int maxn = 501;
    static const long long LIM = 1e18 + 31;
    int a[maxn][maxn];
    long long tr[maxn];
    int n,m;

    void Kadane1D(int i, int k, int& l, int& r, long long& lbest){
        long long sum = 0ll;
        int pre = 1;
        up(j,1,m){
            tr[j] += 1ll*a[k][j];
            sum += tr[j];
            if (sum < 0ll){
                sum = 0ll;
                pre = j+1;
            }
            else if (sum > lbest){
                lbest = sum;
                l = pre;
                r = j;
            }
            if (k == n) tr[j] = 0;
        }
    }

    void Kadane2D(){
        cin >> n >> m;
        up(i,1,n) up(j,1,m) cin >> a[i][j];

        long long gbest = -LIM;
        int u,v,x,y;
        u = v = x = y = 1;
        up(i,1,n) up(k,i,n){
            int l = 1;
            int r = 1;
            long long lbest = -LIM;
            Kadane1D(i, k, l, r, lbest);

            if (gbest < lbest){
                gbest = lbest;
                u = i;
                v = k;
                x = l;
                y = r;
            }
        }
        cout << gbest << "\n";
        cout << u << " " << x << " " << v << " " << y << "\n";
    }
} KAN2D;