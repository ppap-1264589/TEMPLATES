// annotshy
/*
  Problem: CIPHER - Dai Ca Di Hoc
*/

#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define Task "CIPHER"
using namespace std;

const int base = 100003;
const long long MM = 1ll * MOD * MOD;
const int maxn = 1005;

int n,m,A,B;
string a[maxn];
long long H[maxn][maxn];

const int p = 307;
const int q = 37;
long long P[maxn],Q[maxn];

void Prepare_Hash_2D(){
    //Prepare power:
    P[0] = 1;
    Q[0] = 1;
    for(int i = 1;i <= m;++i) P[i] = P[i - 1] * p % MOD;
    for(int i = 1;i <= n;++i) Q[i] = Q[i - 1] * q % MOD;
    //Prepare Hashing (1 1) -> (i j)
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= m;++j) {
            H[i][j] = (H[i][j - 1] * p % MOD + H[i - 1][j] * q % MOD) % MOD;
            H[i][j] = (H[i][j] - H[i - 1][j - 1] * p * q + MM + a[i][j]) % MOD;
        }
}

long long Get_Hash_2D(int a,int b,int x,int y) {
    long long Hash = (H[x][y] - H[a - 1][y] * Q[x - a + 1] % MOD - H[x][b - 1] * P[y - b + 1] + MM) % MOD;
    Hash = (Hash + H[a - 1][b - 1] * Q[x - a + 1] % MOD * P[y - b + 1] % MOD) % MOD;
    return Hash;
}

vector<pair<int,int> > ans;
map<long long,int> M;

void Solve(){
    int mx = 0;
    long long Max_Hash;
    for(int i = A;i <= n;++i)
        for(int j = B;j <= m;++j) {
            long long Hash = Get_Hash_2D(i - A + 1,j - B + 1,i,j);
            if(++M[Hash] > mx) {
                mx = M[Hash];
                Max_Hash = Hash;
            }
        }
    for(int i = A;i <= n;++i)
        for(int j = B;j <= m;++j) {
            long long Hash = Get_Hash_2D(i - A + 1,j - B + 1,i,j);
            if(Hash == Max_Hash) ans.pb({i - A + 1,j - B + 1});
        }
    int L = ans[0].F,R = ans[0].S;
    cout << A << " " << B << "\n";
    for(int i = L;i <= L + A - 1;++i){
        for(int j = R;j <= R + B - 1;++j){
            cout << a[i][j];
        }
        cout << "\n";
    }
    cout << ans.size() << "\n";
    for(auto x : ans) cout << x.F << " " << x.S << "\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cout.tie(0); cin.tie(0);
	if(fopen(Task".inp","r")){
		freopen(Task".inp","r",stdin);
		freopen(Task".out","w",stdout);
	}
    cin >> n >> m;
    string nothing; getline(cin,nothing);
    for(int i = 1;i <= n;++i){
        getline(cin,a[i]);
        a[i] = " " + a[i];
    }
    cin >> A >> B;
    Prepare_Hash_2D();
    Solve();
}

// V T AN
