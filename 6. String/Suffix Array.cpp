struct Suffix_Array{
    static const int maxn = 4e5 + 10;
    static const int LOG = log2(maxn)+2;
    int n;

    pair<pii, int> L[maxn]; //Lexicography order: of string at position have rank i -> start at position L[i].second
    int R[LOG][maxn]; //Ranking of string start at position i, have length of 2^log -> have rank R[log][i]
    int SA[maxn];

    void build_SA(const string& s){
        up(i,1,n) R[0][i] = s[i];

        for (int POW = 1; (1 << (POW-1)) <= n; POW++){
            up(i,1,n){
                L[i].f.f = R[POW-1][i];
                int k = i + (1 << (POW-1));
                if (k <= n) L[i].f.s = R[POW-1][k];
                else L[i].f.s = -1;
                L[i].s = i;
            }
            sort(L+1, L+n+1);

            int cnt = 0;
            up(i,1,n){
                if (L[i].f == L[i-1].f) R[POW][L[i].s] = R[POW][L[i-1].s];
                else R[POW][L[i].s] = ++cnt;
            }
        }

        up(i,1,n) SA[i] = L[i].s;
    }

    int LCP[maxn];
    int pos[maxn];
    void Kasai(const int SA[], const string& s){
        up(i,1,n) pos[SA[i]] = i;

        int k = 0;
        up(i,1,n){
            int& cur = pos[i];
            int j = SA[cur-1];
            //if suffix pair at position (i, j), have rank (cur, cur-1) and LCP equal to k
            //then suffix pair at position (i+1, j'), have rank(cur', cur'-1) should have LCP at least k-1, and at most...
            //find at at most on this line :)
            while (i+k <= n && j+k <= n && s[i+k] == s[j+k]) ++k;
            LCP[cur] = k;
            if (k) --k;
        }
    }

    void make_SA_and_LCP(){
        string s;
        cin >> s;
        n = s.size();
        build_SA(s);
        Kasai(SA, s);
    }







    //Other applications
    int lexi_compare(int i, int j, int l){
        int k = log2(l);
        pair<int, int> a = make_pair(R[k][i], R[k][i+l - (1 << k)]);
        pair<int, int> b = make_pair(R[k][j], R[k][j+l - (1 << k)]);
        return (a == b ? 0 : a < b ? -1 : 1);
    }

    int LCP_2suff(int i, int j){
        int ans = 0;
        for (int k = log2(n); k >= 0; k--) {
            if (R[k][i] == R[k][j]) {
                ans += 1 << k;
                i += 1 << k;
                j += 1 << k;
            }
        }
        return ans;
    }

    long long Number_of_Distinct_Substrings(){
        long long x = 0ll;
        up(i,1,n) x += 1ll*LCP[i];
        return 1ll*n*(n+1)/2 - x;
    }

    string Longest_Common_Consecutive_Substring(string X, string Y){
        string s = X + '@' + Y + "$";
        int n = s.size();

        int pivot = X.size()+1;
        build_SA(s);
        Kasai(SA, s);

        int maxx = 0;
        int id = 0;
        up(i,1,n){
            bool left = SA[i-1] < pivot;
            bool right = SA[i] >= pivot;
            if (left == right) {
                if (maxx < LCP[i]){
                    maxx = LCP[i];
                    id = i;
                }
            }
        }

        if (id == 0) return "not found";
        return s.substr(SA[id]-1, maxx);
    }








    //count pattern inside a string
    int check(int pos, string g, const string& s){
        int f = -1;
        int k = g.size();
        int j = SA[pos];
        int suffix_len = n-j+1;

        if (suffix_len >= k) f = 0;
        g.insert(g.begin(), char(254));
        up(i,1,min(k, suffix_len)){
            if (s[j+i-1] < g[i]) return -1;
            if (s[j+i-1] > g[i]) return 1;
        }
        return f;
    } //suffix SA[pos]'th compared to g?

    int Left_Most(string g, const string& s){
        int l = 0;
        int r = n;
        int flag = 0;
        while (r - l > 1){
            int mid = l + (r-l)/2;
            flag = check(mid, g, s);
            if (flag >= 0) r = mid;
            else l = mid;
        }
        if (check(r, g, s) != 0) return -1;
        return r;
    }

    int Right_Most(string g, const string& s){
        int l = 1;
        int r = n+1;
        int flag = 0;
        while (r - l > 1){
            int mid = l + (r-l)/2;
            flag = check(mid, g, s);
            if (flag <= 0) l = mid;
            else r = mid;
        }
        if (check(l, g, s) != 0) return -1;
        return l;
    }

    int Count_Pattern_Inside_a_string(string s){
        n = s.size();
        s = '@' + s;
        string g;
        cin >> g;
        int Left = Left_Most(g, s);
        int Right = Right_Most(g, s);
        int res = -1;
        if (Left == -1 || Right == -1) res = 0;
        else if (Left != -1 && Right != -1) res = Right - Left + 1;
        return res;
    }
} my_suffix;