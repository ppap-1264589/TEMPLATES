struct Parallel_BS{
    static const int maxn = 1e5 + 10;
    int par[maxn], cnt[maxn];
    int L[maxn], R[maxn];
    int n,m,q;
    struct Query{
        int x,y;
        int need;
    } Q[maxn];
    vector<int> Group[maxn];
    pair<int, int> edge[maxn];

    int root(int x){
        if (par[x] == 0) return x;
        return par[x] = root(par[x]);
    }

    void Union(int u, int v){
        u = root(u);
        v = root(v);
        if (u == v) return;
        if (cnt[u] < cnt[v]) swap(u,v);
        par[v] = u;
        cnt[u] += cnt[v];
    }

    void solve(){
        cin >> n >> m;
        up(i,1,m) cin >> edge[i].u >> edge[i].v;

        cin >> q;
        up(i,1,q){
            cin >> Q[i].x >> Q[i].y >> Q[i].need;
            R[i] = m;
        }

        for (int loop = int(ceil(log2(m))); loop; loop--){
            up(i,1,n) par[i] = 0, cnt[i] = 1;

            up(i,1,q) if (R[i] - L[i] > 1){
                Group[(L[i] + R[i])/2].ep(i);
            }

            up(i,1,m){
                Union(edge[i].u, edge[i].v);
                for (int& t : Group[i]){
                    int u = root(Q[t].x);
                    int v = root(Q[t].y);
                    int sum;
                    if (u == v) sum = cnt[u];
                    else sum = cnt[u] + cnt[v];

                    if (sum >= Q[t].need) R[t] = i;
                    else L[t] = i;
                }
                Group[i].clear();
            }
        }

        up(i,1,q) cout << R[i] << "\n";
    }
} PBS;