struct Kth_Shortest_Path{
    static const int maxn = 10001;
    vector<pii> a[maxn];
    int n,m;
    int k;
    priority_queue<pii, vector<pii>, greater<pii>> P;
    vector<vector<int>> d;

    void input(){
        int u,v,w;
        cin >> n >> m;
        cin >> k;
        up(i, 1, m){
            cin >> u >> v >> w;
            a[u].pb({v, w});
            a[v].pb({u, w});
        }
        d.resize(n+1, vector<int>());
    }

    void Dijkstra(){
        P.push({0, 1});
        while (!P.empty()){
            int u = P.top().s;
            int curw = P.top().f;
            P.pop();
            if ((d[u].size() != 0 && d[u].back() == curw) || d[u].size() >= k) continue;
            d[u].ep(curw);

            for (pii x : a[u]){
                int v = x.f;
                int w = x.s;
                int val = curw + w;

                if (d[v].size() != 0 && d[v].back() == val || d[v].size() >= k) continue;
                P.push({val, v});
            }
        }
    }

    void solve(){
        in();
        Dijkstra();
        if (d[n].size() == 0) return cout << -1, 0;
        for (int x : d[n]) cout << x << " ";
        return 0;
    }
} KTH_SHORTEST;
// find the Kth Shortest path in a graph