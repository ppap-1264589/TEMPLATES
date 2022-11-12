const int maxn = 1e2 + 10;
const int MOD = 1e9 + 7;
int n,m,k;

struct Matrix{
    int c[maxn][maxn];

    void init(){
        memset(c, 0, sizeof(c));
    }

    Matrix operator * (const Matrix& A){
        Matrix res;
        up(i,1,n) up(j,1,n){
            res.c[i][j] = 0;
            up(k,1,n){
                res.c[i][j] = (1ll*c[i][k]*A.c[k][j] + res.c[i][j]) % MOD;
            }
        }
        return res;
    }

    Matrix Unit(){
        Matrix res;
        up(i,1,n) up(j,1,n){
            if (i == j) res.c[i][j] = 1;
            else res.c[i][j] = 0;
        }
        return res;
    }

    Matrix fpow(Matrix A, int n){
        Matrix res = Unit();
        for (; n; n >>= 1, A = A*A){
            if (n & 1) res = A*res;
        }
        return res;
    }
};

void solve(){
    Matrix A;
    A.init();
    //input for A.c[u][v];

    int k = 2; //number of exponentiation
    A = A.fpow(A, k);

    cout << A.c[1][1];
}