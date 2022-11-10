struct EdmondsKarp{
    static const int maxn = 1001;
    int c[maxn][maxn];
    int f[maxn][maxn];
    vector<int> a[maxn];
    int tr[maxn];
    int n,m,s,t;
    int maxflow;
    queue<int> Q;

    void in(){
        cin >> n >> m >> s >> t;
        int u,v,w;
        up(i,1,m){
            cin >> u >> v >> w;
            a[u].push_back(v);
            a[v].push_back(u);
            c[u][v] = w;
        }
    }

    bool argument_path_found(){
        Q = queue<int>{};
        memset(tr, 0, sizeof(tr));

        tr[s] = -1;
        Q.push(s);
        while (!Q.empty()){
            int u = Q.front();
            Q.pop();
            if (u == t) return true;
            for (int v : a[u]){
                if (tr[v] == 0 && f[u][v] < c[u][v]){
                    tr[v] = u;
                    Q.push(v);
                }
            }
        }
        return false;
    }

    void IncFlow(){
        int delta = 1000000007;
        int v = t;
        while (v != s){
            int u = tr[v];
            delta = min(delta, c[u][v] - f[u][v]);
            v = u;
        }

        v = t;
        while (v != s){
            int u = tr[v];
            f[u][v] += delta;
            f[v][u] -= delta;
            v = u;
        }
        maxflow += delta;
    }

    void solve(){
        in();
        while (argument_path_found()){
            IncFlow();
        }
        cout << maxflow;
    }
} BFS_FLOW;
