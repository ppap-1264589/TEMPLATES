const int maxn = 1e5 + 10;
struct Query{
    int u,v,t;
};
struct DSU_save{
    int u,v,su,sv;
};

struct DSU_with_rollback{
    int par[maxn];
    stack<DSU_save> save;
    int comps;

    void init(int n){
        assert(save.empty());
        memset(par, -1, sizeof(par[0])*(n+1));
        comps = n;
    }

    int root(int x){
        while (par[x] >= 0) x = par[x];
        return x;
    }

    bool combinable(int u, int v){
        u = root(u);
        v = root(v);
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        save.push({u, v, par[u], par[v]});
        --comps;
        par[u] += par[v];
        par[v] = u;
        return true;
    }

    bool connected(int u, int v){
        return (root(u) == root(v));
    }

    void rollback(){
        if (save.empty()) return; //in fact: "vector<DSU_save>save" never empty
        DSU_save cur = save.top();
        save.pop();
        ++comps;
        par[cur.u] = cur.su;
        par[cur.v] = cur.sv;
    }
};

struct Segment_Tree{
    int n;
    vector<vector<Query> > T;
    int conn[maxn];
    DSU_with_rollback dsu;

    void init(int _n, int _q){ //be careful: number of n and q
        n = _q;
        T.clear();
        T.resize((n << 2) + 5);
        dsu.init(_n);
        memset(conn, -1, sizeof(conn[0])*(n+1));
    }

    void add_node(int nod, int l, int r, int u, int v, const Query& Q){
        if (l > v || r < u) return;
        if (l >= u && r <= v){
            T[nod].push_back(Q);
            return;
        }
        int mid = (l+r) >> 1;
        add_node(nod*2, l, mid, u, v, Q);
        add_node(nod*2+1, mid+1, r, u, v, Q);
    }

    void DFS(int nod, int l, int r){
        int rollcount = 0;
        for (Query& Q : T[nod]){
            if (Q.t == -1 && dsu.combinable(Q.u, Q.v)) ++rollcount;
        }

        if (l == r){ //Reach the Query point
            for (Query& Q : T[nod]) if (Q.t > 0){
                conn[l] = dsu.connected(Q.u, Q.v);
            }
        }
        else {
            int mid = (l+r) >> 1;
            DFS(nod*2, l, mid);
            DFS(nod*2+1, mid+1, r);
        }
        while (rollcount--) dsu.rollback();
    }

    void add_node(int l, int r, const Query& Q){
        add_node(1, 1, n, l, r, Q);
    }

    void answer(vector<int>& query_pos){
        for (int& i : query_pos) cout << conn[i];
    }
} Tree;


int n,q;
vector<int> query_pos;
map<pii, stack<int> > M;
void build_tree(){
    string k;
    int type,u,v;
    up(i,1,q){
        cin >> k >> u >> v;
        if (k == "1") type = 1;
        else if (k == "2") type = 2;
        else type = 3;

        if (type == 3) query_pos.push_back(i);
        if (u > v) swap(u,v);
        pii cur = {u, v};

        if (type == 1) M[cur].push(i);
        else if (type == 2){
            if (M[cur].empty()) continue;
            Tree.add_node(M[cur].top(), i, {u, v, -1});
            M[cur].pop();
        }
        else Tree.add_node(i, i, {u, v, i}); // type == "conn"
    }

    for (auto& rest : M){
        int u = rest.f.f;
        int v = rest.f.s;
        while (!rest.s.empty()){
            Tree.add_node(rest.s.top(), q, {u, v, -1});
            rest.s.pop();
        }
    }
}

void solve(){
    cin >> n >> q;
    Tree.init(n, q);
    build_tree();
    Tree.DFS(1, 1, q);
    Tree.answer(query_pos);
}