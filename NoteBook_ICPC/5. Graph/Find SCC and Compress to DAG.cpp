struct Find_SCC{
    static const int maxn = 1e5 + 10;
    vector<int> a[maxn];
    vector<int> b[maxn];
    int n,m;
    int low[maxn], idx[maxn], deg[maxn];
    int tdfs, SCC;
    int inSCC[maxn];
    stack<int> st;
    bitset<maxn> exist;

    void Tarjan(int& u){
        low[u] = idx[u] = ++tdfs;
        st.push(u);
        for (int& v : a[u]){
            if (inSCC[v]) continue;
            if (!idx[v]){
                Tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else low[u] = min(low[u], idx[v]);
        }

        if (low[u] == idx[u]){
            SCC++;
            while (true){
                int v = st.top();
                st.pop();
                inSCC[v] = SCC;
                if (u == v) break;
            }
        }
    }

    void resetdata(){
        up(i,1,n){
            a[i].clear();
            b[i].clear();
        }
        memset(idx, 0, 4*(n+1));
        memset(inSCC, 0, 4*(n+1));
        memset(deg, 0, 4*(n+1));
        exist.reset();
        SCC = tdfs = 0;
    }

    void prepare(){
        cin >> n >> m;
        int u,v;
        up(i,1,m){
            cin >> u >> v;
            a[u].ep(v);
            exist[u] = exist[v] = 1;
        }

        up(i,1,n) if (!idx[i] && exist[i]) Tarjan(i);
    }

    void compress_to_DAG(){
        up(u,1,n) if (exist[u]){
            for (int& v : a[u]){
                int ui = inSCC[u];
                int vi = inSCC[v];
                if (ui != vi) b[ui].ep(vi);
            }
        }
    }

    void solve(){
        prepare();
        compress_to_DAG();
        resetdata();
    }
} FINDSCC;