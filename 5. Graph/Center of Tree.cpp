
struct Center_of_Tree{
    static const int maxn = 100001;
    int cost[maxn];
    int dx[maxn];
    int dy[maxn];
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

    void DFS(int u, int par, int d[]){
        for (pii x : a[u]){
            int v = x.f;
            int w = x.s;
            if (v == par) continue;
            d[v] = d[u] + w;
            DFS(v, u, d);
        }
    }

    void solve(){
        in();
        DFS(1, -1, cost);
        int X = max_element(cost+1, cost+n+1) - cost;
        DFS(X, -1, dx);
        int Y = max_element(dx+1, dx+n+1) - dx;
        DFS(Y, -1, dy);

        int minn = MOD;
        up(i,1,n) minn = min(minn, max(dx[i], dy[i]));
        cout << minn;
    }

    //Center of Tree is the position such that
    //the Longest path from this node to all other nodes
    //is minimal
} my_center_of_tree;