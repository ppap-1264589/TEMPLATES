struct Sparse2D{
    static const int maxn = 500 + 1;
    static const int maxm = 8 + 1;
    int n,m;
    int sp[maxm][maxm][maxn][maxn];
    int logg[maxn];

    void input(){
        cin >> n >> m;
        up(i,1,n) up(j,1,m) cin >> sp[0][0][i][j];
        up(i,2,500) logg[i] = logg[(i >> 1)] + 1;
    }

    void build_sparse(){
        up(u,1,n) up(j,1,8){
            for (int v = 1; v + (1 << j) - 1 <= m; v++){
                sp[0][j][u][v] = min(sp[0][j-1][u][v], sp[0][j-1][u][v + (1 << (j-1))]);
            }
        }

        up(i,1,8) up(j,0,8){
            for (int u = 1; u + (1 << i) - 1 <= n; u++){
                for (int v = 1; v + (1 << j) - 1 <= m; v++){
                    sp[i][j][u][v] = min(sp[i-1][j][u][v], sp[i-1][j][u + (1 << (i-1))][v]);
                }
            }
        }
    }

    int getmin(int u, int v, int p, int q){   //upper left (u, v) and lower right (p, q)
        int k = logg[p-u+1];     //do dai hang
        int l = logg[q-v+1];     //do dai cot
        int r = p - (1 << k) + 1;
        int s = q - (1 << l) + 1;
        int m1 = sp[k][l][u][v];
        int m2 = sp[k][l][u][s];
        int m3 = sp[k][l][r][v];
        int m4 = sp[k][l][r][s];

        return min({m1, m2, m3, m4});
    }
} SP2D;

