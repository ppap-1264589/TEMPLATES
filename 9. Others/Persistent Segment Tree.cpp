const int maxn = 1e5 + 10;
const int LOG = log2(maxn)+2;
int a[maxn];
struct PST_node{
    int l,r,sum;
};
PST_node T[maxn*LOG];
int cnt = 0;
int n,q;


int ROOT[maxn];

void push_up(int nod){
    T[nod].sum = T[T[nod].l].sum + T[T[nod].r].sum;
}

void update(int& nod, int prev_nod, int l, int r, int pos, int val){
    nod = ++cnt;
    T[nod] = T[prev_nod];
    if (l == r){
        T[nod].sum += val;
        return;
    }
    int mid = (l+r) >> 1;
    if (pos <= mid) update(T[nod].l, T[prev_nod].l, l, mid, pos, val);
    else update(T[nod].r, T[prev_nod].r, mid+1, r, pos, val);
    push_up(nod);
}

int sum(int nod, int l, int r, int u, int v){
    if (u > v) return 0;
    if (l > v || r < u) return 0;
    if (l >= u && r <= v) return T[nod].sum;
    int mid = (l+r) >> 1;
    int L = sum(T[nod].l, l, mid, u, v);
    int R = sum(T[nod].r, mid+1, r, u, v);
    return L+R;
}

int Kth(int& nod, int& prev_nod, int l, int r, int k){
    if (l == r) return l;
    int mid = (l+r) >> 1;
    int CNT = T[T[nod].l].sum - T[T[prev_nod].l].sum;
    if (CNT >= k) return Kth(T[nod].l, T[prev_nod].l, l, mid, k);
    return Kth(T[nod].r, T[prev_nod].r, mid+1, r, k - CNT);
}

vector<int> V;
void example(){
    cin >> n >> q;
    up(i,1,n){
        cin >> a[i];
        V.push_back(a[i]);
    }
    sort(all(V));
    V.resize(unique(all(V)) - V.begin());
    up(i,1,n) {
        int x = lower_bound(all(V), a[i]) - V.begin() + 1;
        update(ROOT[i], ROOT[i-1], 1, n, x, 1);
    }

    V.clear();
    V.push_back(-1e9 - 7);
    up(i,1,n) V.push_back(a[i]);
    sort(all(V));
    V.resize(unique(all(V)) - V.begin());

    up(i,1,q){
        int l,r,k;
        cin >> l >> r >> k;
        int x = Kth(ROOT[r], ROOT[l-1], 1, n, k);
        cout << V[x] << "\n";
    }
}