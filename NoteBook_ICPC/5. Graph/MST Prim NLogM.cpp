struct Prim_ONlogN{
    static const int maxn = 3e4+10;
    static const int LIM = 1e9+7e8;
    int n,m;
    vector<pii> a[maxn];
    int dist[maxn];
    int connect[maxn];
    long long ans = 0;
    ///distance

    priority_queue<pii, vector<pii>, greater<pii> > Q;

    void Prim(int root){
        memset(dist, 0x3f, (n+1)*sizeof(dist[0]));
        dist[root] = 0;
        Q.push(make_pair(0, root));

        while (!Q.empty()){
            int curw = Q.top().f;
            int u = Q.top().s;
            Q.pop();
            if (curw > dist[u]) continue;

            ans += dist[u];
            dist[u] = -LIM;

            for (pii x : a[u]){
                int w = x.s;
                int v = x.f;
                if (dist[v] > w){
                    dist[v] = w;
                    connect[v] = u;
                    Q.push(make_pair(dist[v], v));
                }
            }
        }
    }

    void solve(){
        cin >> n >> m;
        int u,v,w;
        up(i, 1, m){
            cin >> u >> v >> w;
            a[u].pb({v, w});
            a[v].pb({u, w});
        }
        Prim(1);
        cout << ans << "\n";
    }
} PRIM_NLOGN;