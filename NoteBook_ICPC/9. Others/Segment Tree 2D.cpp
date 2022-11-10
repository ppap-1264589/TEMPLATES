const int maxn = 1e3 + 10;
const int LIM = 1e9 + 7;
int n,m,a,b,c,d;
int P[maxn][maxn];
int S[maxn][maxn];

int sum(int ux, int vx, int uy, int vy){
    return P[vx][vy] - P[ux-1][vy] - P[vx][uy-1] + P[ux-1][uy-1];
}

int T[maxn << 2][maxn << 2];
void buildY(int nodx, int lx, int rx, int nody, int l, int r){
    if (l == r){
        if (lx == rx){
            T[nodx][nody] = S[lx][l];
        }
        else T[nodx][nody] = min(T[nodx*2][nody], T[nodx*2+1][nody]);
        return;
    }
    int mid = (l+r) >> 1;
    buildY(nodx, lx, rx, nody*2, l, mid);
    buildY(nodx, lx, rx, nody*2+1, mid+1, r);
    T[nodx][nody] = min(T[nodx][nody*2], T[nodx][nody*2+1]);
}

void buildX(int nod, int l, int r){
    if (l != r){
        int mid = (l+r) >> 1;
        buildX(nod*2, l, mid);
        buildX(nod*2+1, mid+1, r);
    }
    buildY(nod, l, r, 1, 1, m);
}

int queryY(int nodx, int nody, int l, int r, int u, int v){
    if (l > v || r < u) return LIM;
    if (l >= u && r <= v) return T[nodx][nody];
    int mid = (l+r) >> 1;
    int L = queryY(nodx, nody*2, l, mid, u, v);
    int R = queryY(nodx, nody*2+1, mid+1, r, u, v);
    return min(L, R);
}

int queryX(int nod, int l, int r, int ux, int vx, int uy, int vy){
    if (l > vx || r < ux) return LIM;
    if (l >= ux && r <= vx) return queryY(nod, 1, 1, m, uy, vy);
    int mid = (l+r) >> 1;
    int L = queryX(nod*2, l, mid, ux, vx, uy, vy);
    int R = queryX(nod*2+1, mid+1, r, ux, vx, uy, vy);
    return min(L, R);
}

void build2D(){
    buildX(1, 1, n);
}

int query2D(int ux, int vx, int uy, int vy){
    return queryX(1, 1, n, ux, vx, uy, vy);
}