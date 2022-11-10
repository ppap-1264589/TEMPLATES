struct DP_on_DAG{
    static const int maxn = 1e5 + 10;
    vector<pair<int, int>> a[maxn];
    int n,m;
    int f[maxn];

    int DFS(int u){
        if (f[u] != -1) return f[u];
        f[u] = 0;
        for (pii x : a[u]){
            int v = x.f;
            int w = x.s;
            f[u] = max(f[u], DFS(v) + w);
        }
        return f[u];
    }

    void input(){
        cin >> n >> m;
        int u,v,w;
        up(i,1,m){
            cin >> u >> v >> w;
            a[u].push_back({v, w});
        }
    }

    void solve(){
        memset(f, -1, sizeof(f));
        up(i,1,n) f[i] = DFS(i);
        cout << *max_element(f+1, f+n+1);
    }
} DP_DAG;