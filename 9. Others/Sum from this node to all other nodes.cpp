const int maxn = 2e5 + 10;
long long under[maxn];
long long h[maxn];
long long D[maxn];
vector<int> a[maxn];
int n;

void preDFS(int u, int par){
    under[u] = 1;
    for (int v : a[u]){
        if (v == par) continue;
        h[v] = h[u] + 1;
        preDFS(v, u);
        under[u] += under[v];
    }
}

void sumDist(int u, int par, int N){
    for (int v : a[u]){
        if (v == par) continue;
        D[v] = D[u] + 1ll*N - 1ll*2*under[v];
        sumDist(v, u, N);
    }
}

void solve(){
    cin >> n;
    int u,v;
    up(i,1,n-1){
        cin >> u >> v;
        a[u].ep(v);
        a[v].ep(u);
    }
    preDFS(1, -1);
    up(i,1,n) D[1] += 1ll*h[i];
    sumDist(1, -1, n);
    up(i,1,n) cout << D[i] << " ";
}