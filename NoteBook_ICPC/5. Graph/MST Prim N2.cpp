struct Prim_ON2{
    static const int maxn = 5050;
    const double LIM = 2e18;

    bool is0[maxn][maxn];
    bool marked[maxn];
    double dist[maxn];
    double sum_MST = 0;
    int connect[maxn];
    int n,m;

    double sqr(int x){
        return x*x;
    }

    double W(int u, int v){return 0;} //weight between u and v

    void Forward(int u){
        marked[u] = true;
        up(v,1,n){
            if (v == u) continue;
            double w = W(u, v);
            if (!marked[v] && dist[v] > w) {
                dist[v] = w;
                connect[v] = u;
            }
        }
    }

    void Prim(int root){
        up(i,0,n+1) dist[i] = LIM;
        dist[root] = 0;

        up(loop,1,n){
            int next = -1;
            up(v,1,n){
                if (!marked[v] && (next == -1 || dist[next] > dist[v])) next = v;
            }
            if (next == -1) break;
            sum_MST += dist[next];
            Forward(next);
        }
    }

    void solve(){
        ///input
        Prim(1);
        cout << sum_MST;
    }
} PRIM;