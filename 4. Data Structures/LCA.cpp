struct LCA{
    static const int maxn = 100001;
    static const int LIM = 1e9 + 7;
    int n;
    vector<pii> a[maxn];
    int minpar[maxn][18];
    int maxpar[maxn][18];
    int par[maxn][18];
    int h[maxn];

    void in(){
        int u,v,w;
        cin >> n;
        up(i,1,n-1){
            cin >> u >> v >> w;
            a[u].pb({v, w});
            a[v].pb({u, w});
        }
    }

    void DFS(int u, int parent){
        for (pii x : a[u]){
            int v = x.f;
            int w = x.s;
            if (v == parent) continue;
            h[v] = h[u] + 1;
            par[v][0] = u;
            minpar[v][0] = w;
            maxpar[v][0] = w;

            up(i,1,17){
                int p = par[v][i-1];
                par[v][i] = par[p][i-1];
                minpar[v][i] = min(minpar[v][i-1], minpar[p][i-1]);
                maxpar[v][i] = max(maxpar[v][i-1], maxpar[p][i-1]);
            }

            DFS(v, u);
        }
    }

    pair<int, int> MinMaxLCA(int u, int v){
        int Fmin = LIM;
        int Fmax = -LIM;
        if (h[u] < h[v]) swap(u, v);

        int de = h[u] - h[v];
        down(i, log2(de), 0){
            if (bit(de, i)){
                Fmin = min(Fmin, minpar[u][i]);
                Fmax = max(Fmax, maxpar[u][i]);
                u = par[u][i];
            }
        }

        if (u == v) return make_pair(Fmin, Fmax);

        down(i, 17, 0){
            if (par[u][i] != par[v][i]){
                Fmin = min(Fmin, min(minpar[u][i], minpar[v][i]));
                Fmax = max(Fmax, max(maxpar[u][i], maxpar[v][i]));
                u = par[u][i];
                v = par[v][i];
            }
        }

        Fmin = min(Fmin, min(minpar[u][0], minpar[v][0]));
        Fmax = max(Fmax, max(maxpar[u][0], maxpar[v][0]));
        return make_pair(Fmin, Fmax);
    } //Max and Min on path from u to v

    void query(){
        int u,v;
        cin >> u >> v;
        pair<int, int> res = MinMaxLCA(u, v);
    }




     //DP for least lexicography order
    int pmin[maxn][17];
    bool isbetter(int u, int v){
        int PminU = n+1;
        int PminV = n+1;
        down(i, 17, 0){
            if (par[u][i] != par[v][i]){
                PminU = min(PminU, pmin[u][i]);
                PminV = min(PminV, pmin[v][i]);
                u = par[u][i];
                v = par[v][i];
            }
        }
        PminU = min(PminU, pmin[u][0]);
        PminV = min(PminV, pmin[v][0]);
        return (PminU < PminV);
    }

    int tr[maxn];
    void DP(int u){
        pmin[u][0] = u;
        par[u][0] = tr[u];
        up(i, 1, 17){
            int p = par[u][i-1];
            par[u][i] = par[p][i-1];
            pmin[u][i] = min(pmin[u][i-1], pmin[p][i-1]);
        }

        // Usage:
        // if (tr[u] == 0 || isbetter(v, tr[u])) tr[u] = v;
    }
} my_LCA;