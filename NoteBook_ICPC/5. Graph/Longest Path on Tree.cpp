struct Longest_Path_on_Tree{
    static const int maxn = 1e5 + 10;
    int d[maxn];
    vector<pii> a[maxn];
    int n;

    void in(){
        cin >> n;
        int u,v,w;
        up(i, 1, n-1){
            cin >> u >> v >> w;
            a[u].pb({v, w});
            a[v].pb({u, w});
        }
    }

    void DFS(int u, int par){
        for (pii x : a[u]){
            int v = x.f;
            int w = x.s;
            if (v == par) continue;
            d[v] = d[u] + w;
            DFS(v, u);
        }
    }

    void solve(){
        in();
        DFS(1, -1);
        int x = max_element(d+1, d+n+1) - d;
        memset(d, 0, sizeof(d));
        DFS(x, -1);
        cout << *max_element(d+1, d+n+1);
    }
} my_LPOT;