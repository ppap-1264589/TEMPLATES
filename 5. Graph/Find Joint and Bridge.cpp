struct Bridge_Joint{
    static const int maxn = 100002;
    int n, m, par[maxn];
    vector<int> a[maxn];
    int num[maxn], low[maxn];
    vector<pii> Bridge;
    vector<int> Joint;
    int tdfs;

    void DFS(int u){
        int child = bool(par[u] != -1); // bool == 0 khi u la goc DFS
        low[u] = num[u] = ++tdfs;
        for (int v : a[u]){
            if (v == par[u]) continue;
            if (!num[v]){
                par[v] = u;
                DFS(v);
                low[u] = min(low[u], low[v]);
                if (low[v] == num[v]){
                    Bridge.push_back({min(u, v), max(u, v)});
                }
                if (low[v] >= num[u]) child++;
            }
            else low[u] = min(low[u], num[v]);
        }
        if (child > 1) Joint.emplace_back(u);
    }

    void input(){
        cin >> n >> m;
        up(i, 1, m){
            int u,v;
            cin >> u >> v;
            a[u].ep(v);
            a[v].ep(u);
        }
    }

    void Find_Bridge_Joint(){
        up(i,1,n){
            if (!par[i]){
                par[i] = -1;
                DFS(i);
            }
        }
    }
} F_BJ;