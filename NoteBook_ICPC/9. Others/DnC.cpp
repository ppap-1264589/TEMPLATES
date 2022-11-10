const int maxn = 1e5 + 10;
int dp[11][maxn];
int n,k;

int cost(int l, int r){ return 0; }
//This should be done in O(1) or O(log)

void DIVIDE(int before[], int f[], int l, int r, int pl, int pr){
    if (l > r) return;

    int mid = (l+r) >> 1;
    int halve = pl;

    for (int i = pl; i <= min(mid-1, pr); i++){
        int val = before[i] + cost(i+1, mid);
        if (val <= f[mid]){
            f[mid] = val;
            halve = i;
        }
    }

    DIVIDE(before, f, l, mid-1, pl, halve);
    DIVIDE(before, f, mid+1, r, halve, pr);
}

void solve(){
    up(i,1,k){
        DIVIDE(dp[i-1], dp[i], i, n, i-1, n-1);
    }
    cout << dp[k][n];
}
