struct Heavy_Light_Decomposition{
    const static int maxn = 1e5 + 10;
    vector<int> a[maxn];
    static int n,R;
    //numnode, root of tree
    static int W[maxn];
    //weight of node
    static int Tsize[maxn], heavy[maxn], par[maxn];
    //size of tree, heavy node, parent of node

    void DFS(int& u){
        Tsize[u] = 1;
        heavy[u] = -1;
        int id_max = -1;
        for (int i = 0; i < (int)a[u].size(); i++){
            int& v = a[u][i];
            if (v == par[u]) continue;
            par[v] = u;
            DFS(v);
            Tsize[u] += Tsize[v];
            if (id_max == -1 || Tsize[v] > Tsize[a[u][id_max]]){
                id_max = i;
                heavy[u] = v;
            }
        }
    }

    static int in[maxn], out[maxn], node[maxn];
    //intime and outime of substree
    //node order in HLD
    static int HChain[maxn], DChain[maxn];
    //head of chain, depth of chain
    static int thld;
    void HLD(int& u){
        in[u] = ++thld;
        node[thld] = u;
        if (heavy[u] != -1) {
            int v = heavy[u];
            HChain[v] = HChain[u];
            DChain[v] = DChain[u];
            HLD(v);
        }
        for (int& v : a[u]){
            if (v != par[u] && v != heavy[u]){
                HChain[v] = v;
                DChain[v] = DChain[u] + 1;
                HLD(v);
            }
        }
        out[u] = thld;
    }

    static struct NODE{
        long long sum, lazysum;
        int len;
        void init(){
            sum = lazysum = 0ll;
            len = 1;
        }
    } T[maxn << 2];

    static struct Segment_Tree{
    private:
        void push_up(int nod){}

        void push_down(int nod){}

        void Update(int nod, int l, int r, int u, int v, int val){}

        long long Get(int nod, int l, int r, int u, int v){ return 0; }

    public:
        void build(int nod, int l, int r){
            if (l == r){
                T[nod].init();
                T[nod].sum = 1ll*W[node[l]];
                return;
            }
            int mid = (l+r) >> 1;
            build(nod*2, l, mid);
            build(nod*2+1, mid+1, r);
            T[nod].sum = T[nod*2].sum + T[nod*2+1].sum;
            T[nod].len = T[nod*2].len + T[nod*2+1].len;
        }
        void Update(int l, int r, int val){
            Update(1, 1, n, l, r, val);
        }
        long long Get(int l, int r){
            return Get(1, 1, n, l, r);
        }
    } Tree;







    void real_Update(int x, int val){
        while (x != 0){
            Tree.Update(in[HChain[x]], in[x], val);
            x = par[HChain[x]];
        }
    } //update for all parent of node x with val

    long long real_Get(int x, int y){
        long long res = 0;
        while (HChain[x] != HChain[y]){
            if (DChain[x] < DChain[y]) swap(x, y);
            res += Tree.Get(in[HChain[x]], in[x]);
            x = par[HChain[x]];
        }
        if (in[x] > in[y]) swap(x, y);
        res += Tree.Get(in[x], in[y]);
        return res;
    } //sum of all node from node x to y on tree

    void Input(){
        cin >> n >> R;
        up(i,1,n) cin >> W[i];
        up(i,1,n-1){
            int u,v;
            cin >> u >> v;
            a[u].ep(v);
            a[v].ep(u);
        }
    }

    void Process(){
        DFS(R);
        HChain[R] = R;
        DChain[R] = 1;
        HLD(R);
        Tree.build(1, 1, n);
    }

    void Answer(){
        int Q;
        cin >> Q;
        char c;
        int x,y,d;
        while (Q--){
            if (c == 'U'){
                cin >> x >> d;
                real_Update(x, d); // update all parent of node x
            }
            else {
                cin >> x >> y;
                cout << real_Get(x, y) << "\n"; //sum of all node from x to y
            }
        }
    }
} HLD_TREE;