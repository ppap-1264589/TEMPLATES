struct DP_on_DAG_queue{
    static const int maxn = 100001;
    vector<pii> a[maxn];
    int n,m;
    queue<int> q;
    int degin[maxn];
    int f[maxn];

    void in(){
        cin >> n >> m;
        int u,v,w;
        up(i, 1, m){
            cin >> u >> v >> w;
            a[u].push_back({v, w});
            degin[v]++;
        }
    }

    void DP(){
        for (int i = 1; i <= n; i++){
            if (degin[i] == 0) q.push(i);
        }

        while (!q.empty()){
            int u = q.front();
            for (pii x : a[u]){
                int v = x.f;
                int w = x.s;
                if (f[v] < f[u] + w){
                    f[v] = f[u] + w;
                }
                if (--degin[v] == 0) q.push(v);
            }
            q.pop();
        }

        cout << *max_element(f+1, f+n+1);
    }
} DP_DAG_queue;