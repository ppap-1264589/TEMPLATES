const int maxn = 1e3 + 10;
const int maxm = 1e5 + 10;
const int LIM = 1e18 + 10;

struct Edge{
    int u, v;
    int cap;
    int flow = 0;
    Edge(int _u, int _v, int _cap){
        u = _u;
        v = _v;
        cap = _cap;
    }
};

struct Dinitz{
    vector<Edge> E;
    int n,m;
    int s,t;
    vector<int> a[maxn];
    int level[maxn];
    int cur[maxn];
    queue<int> Q;

    Dinitz(int _n, int _s, int _t){
        n = _n;
        s = _s;
        t = _t;
        m = 0;
    }

    void add_edge(int From, int To, int Cap){
        E.push_back(Edge(From, To, Cap));
        E.push_back(Edge(To, From, 0));
        a[From].push_back(m);
        a[To].push_back(m+1);
        m += 2;
    }

    bool BFS(){
        memset(level, -1, sizeof(level[0])*(n+1));
        Q.push(s);
        level[s] = 0;
        while (!Q.empty()){
            int u = Q.front();
            Q.pop();
            for (int id : a[u]){
                int v = E[id].v;
                if (level[v] != -1 || E[id].flow == E[id].cap) continue;
                level[v] = level[u] + 1;
                Q.push(v);
            }
        }
        return (level[t] != -1);
    }

    int DFS(int u, int delta){
        if (u == t) return delta;
        if (delta == 0) return 0;
        for (int& x = cur[u]; x < (int)a[u].size(); x++){
            int id = a[u][x];
            int v = E[id].v;
            if (level[v] != level[u] + 1 || E[id].flow == E[id].cap) continue;

            int cur_flow = min(delta, E[id].cap - E[id].flow);
            int neck = DFS(v, cur_flow);

            if (neck == 0) continue;
            E[id].flow += neck;
            E[id ^ 1].flow -= neck;
            return neck;
        }
        level[u] = LIM;
        return 0;
    }

    int max_flow(){
        int res = 0;
        while (BFS()){
            memset(cur, 0, sizeof(cur[0])*(n+1));
            while (int delta = DFS(s, LIM)){
                res += delta;
            }
        }
        return res;
    }
};

void solve(){
    int n,m,s,t;
    cin >> n >> m >> s >> t;
    Dinitz D(n, s, t);
    int u,v,w;
    while (cin >> u >> v >> w){
        D.add_edge(u, v, w);
    }
    cout << D.max_flow();
}