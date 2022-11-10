struct Ford_Bellman{
    static const int maxn = 100001;
    vector<pii> a[maxn];
    int n,m,s,f;
    int d[maxn];
    int tr[maxn];
    queue<pii> q;

    void in(){
        cin >> n >> m >> s >> f;
        int u,v,w;
        up(i, 1, m){
            cin >> u >> v >> w;
            a[u].pb({v, w});
            a[v].pb({u, w});
        }
    }

    void FordBell(){
        fill(d, d+n+1, 1000001);
        d[s] = 0;
        q.push({s, d[s]});
        while (!q.empty()){
            pii x = q.front();
            q.pop();
            int u = x.first;
            int curw = x.second;
            for (pii ve : a[u]){
                int v = ve.first;
                int w = ve.second;
                if (d[v] > curw + w){
                    d[v] = curw + w;
                    tr[v] = u;
                    q.push({v, d[v]});
                }
            }
        }
    }

    void out(){
        cout << d[f];
        cout << "\n";
        vector<int> path;
        while (s != f){
            path.ep(f);
            f = tr[f];
        }
        path.ep(s);
        cout << path.size() << "\n";
        reverse(path.begin(), path.end());
        for (auto x : path) cout << x << " ";
    }
} FBELL;