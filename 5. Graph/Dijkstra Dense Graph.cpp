struct Dijkstra_Dense_Graph{
    static const int maxn = 1001;
    static const int LIM = 1e9 + 7;
    bitset<maxn> marked;
    int n;
    int st, fi;
    int dist[maxn];
    int C[maxn][maxn];

    void Forward(int u){
        marked[u] = true;
        up(v,1,n) dist[v] = min(dist[v], dist[u] + C[u][v]);
    }

    void Dense_Dijkstra(int root){
        memset(dist, 0x3f, (n+1)*sizeof(dist[0]));
        dist[root] = 0;
        up(loop, 1, n){
            int next = -1;
            up(v,1,n) if (!marked[v] && (next == -1 || dist[next] > dist[v])) next = v;
            if (next == -1) break;
            Forward(next);
        }
    }

    void solve(){
        cin >> n >> st >> fi;
        up(i,1,n) up(j,1,n) cin >> C[i][j];

        Dense_Dijkstra(st);
        cout << dist[fi];
    }
} GDENSE;