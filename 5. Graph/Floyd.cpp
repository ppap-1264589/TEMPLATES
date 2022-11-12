struct Floyd_Warshall{
    static const int maxn = 101;
    vector<pii> a[maxn];
    int n,m;
    int tr[maxn][maxn];
    int cost[maxn][maxn];
    int s,f;

    void in(){
        cin >> n >> m >> s >> f;
        memset(cost, 60, sizeof(cost));
        int u,v,w;
        up(i,1,m){
            cin >> u >> v >> w;
            cost[u][v] = w;
            cost[v][u] = w;
        }
    }

    void Floyd(){
        up(i,1,n) up(j, 1, n){
            tr[i][j] = j;
            if (i == j) cost[i][j] = 0;
        }

        up(k,1,n) up(u, 1, n) up(v, 1, n){
            if (cost[u][v] > cost[u][k] + cost[k][v]){
                cost[u][v] = cost[u][k] + cost[k][v];
                tr[u][v] = tr[u][k];
            }
        }
    }

    void Fpath(){
        vector<int> path;
        while (s != f){
            path.ep(s);
            s = tr[s][f];
        }
        path.ep(f);
        cout << path.size() << "\n";
        for (auto x : path) cout << x << " ";
    }
} FLOYD;