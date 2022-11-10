mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());
struct Bipartite_Matching{
    static const int maxn = 100001;
    vector<int> a[maxn];
    int n,m;
    int matX[maxn];
    int matY[maxn];
    int dd[maxn];

    void input(){
        cin >> m >> n;
        int u,v;
        while (cin >> u >> v) a[u].ep(v);
    }

    bool Kuhn(int u, int cur){
        if (dd[u] == cur) return 0;
        dd[u] = cur;
        for (int v : a[u]){
            if (matX[v] == 0 || Kuhn(matX[v], cur)){
                matX[v] = u;
                matY[u] = v;
                return 1;
            }
        }
        return 0;
    }

    int id[maxn];
    void solve(){
        input();
        int res = 0;
        for (int i = 1; i <= m; i++) id[i] = i;
        shuffle(id+1, id+m+1, RNG);
        for (int i = 1; i <= m; i++){
            if (matY[id[i]] == 0){
                res += Kuhn(id[i], id[i]);
            }
        }
        cout << res << "\n";
        for (int i = 1; i <= n; i++) cout << matX[i] << " ";
    }
} MATCHING;