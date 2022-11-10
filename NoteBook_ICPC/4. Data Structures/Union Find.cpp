struct Disjoint_Set_Union{
    static const int maxn = 2e5 + 10;
    int par[maxn];
    int n;

    int root(int x){
        if (par[x] < 0) return x;
        return par[x] = root(par[x]);
    }

    void Union(int u, int v){
        u = root(u);
        v = root(v);
        if (u == v) return;
        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
    }

    void init(){
        up(i,0,n) par[i] = -1;
    }

    bool Same(int x, int y){
        return root(x) == root(y);
    }

    bool can_destroy(int l, int r){
        bool ok = 1;
        int cur = l;
        int des = get(r+1);
        //r+1 is the index for the whole sector
        while (cur <= r){
            int u = root(cur);
            if (u != cur) ok = 0;
            par[cur] = des;
            cur = u+1;
        }
        return ok;
    } //destroy [l, r], and return 1 if [l, r] was not destroyed before
} DSU;