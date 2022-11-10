struct General_CRT{
    long long addmod(long long a, long long b){
        a %= b;
        if (a < 0) a += b;
        return a;
    }

    struct extype{
        int x,y,d;
    };
    extype exeuclid(int a, int b){
        if (b == 0) return {1, 0, a};
        extype p = exeuclid(b, a%b);
        return {p.y, p.x - a/b*p.y, p.d};
    }

    struct CRTtype{
        bool isSol;
        long long x;
        long long lcm;
    };
    CRTtype CRT(int a, int b, int n, int m){
        extype p = exeuclid(n,m);
        int x = p.x;
        int D = p.d;
        int C = (b - a);
        if (C%D != 0) return {0, -1, -1};
        long long res = addmod(a + 1ll*C/D*x % (m/D) * n, 1ll*m/D*n);
        return {1, res, 1ll*m/D*n};
    }

    static const int maxn = 11;
    int a[maxn];
    int n[maxn];
    int E;

    void solve(){
        cin >> E;
        up(i,1,E) cin >> a[i] >> n[i];
        // a % x = n

        int res = a[1];
        int LCM = n[1];
        up(i,2,E){
            int A,B,N,M;
            A = res;
            B = a[i];
            N = LCM;
            M = n[i];
            auto p = CRT(A, B, N, M);
            if (p.isSol == 0){
                cout << "no solution \n";
                return;
            }
            res = p.x;
            LCM = p.lcm;
        }
        cout << res << " " << LCM << "\n";
    }
} //Find the smallest positive integer x such that 
// a[1] % x = n[1]
// a[2] % x = n[2]
// ...