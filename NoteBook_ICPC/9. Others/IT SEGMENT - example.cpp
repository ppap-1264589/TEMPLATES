const int maxn = 1e5 + 10;

int n;
int x[maxn], w[maxn], e[maxn];

int realval[maxn];
struct LINE{
    int a,b;
    int id;
    int get(const int& x){
        return a*realval[x] + b;
    }
};
LINE T[maxn << 2]; // IT Doan Thang

bitset<maxn << 2> nothing;
pii query(int nod, int l, int r, int pos){
    pii res;
    res = {T[nod].get(pos), T[nod].id};
    if (l == r) return res;

    pii val;
    int mid = (l+r) >> 1;

    if (pos <= mid) val = query(nod*2, l, mid, pos);
    else val = query(nod*2+1, mid+1, r, pos);
    res = max(res, val);
    return res;
}

void update(int nod, int l, int r, int u, int v, LINE Line){
    if (l > v || r < u) return;

    int mid = (l+r) >> 1;
    if (l >= u && r <= v){
        int id1 = T[nod].id;
        int id2 = Line.id;
        pii TL = {T[nod].get(l), id1};
        pii TR = {T[nod].get(r), id1};
        pii LineL = {Line.get(l), id2};
        pii LineR = {Line.get(r), id2};

        if (nothing[nod]){
            nothing[nod] = 0;
            T[nod] = Line;
            return;
        }

        if (TL >= LineL && TR >= LineR){
            return;
        }
        if (TL <= LineL && TR <= LineR){
            T[nod] = Line;
            return;
        }
    }

    update(nod*2, l, mid, u, v, Line);
    update(nod*2+1, mid+1, r, u, v, Line);
}

vector<int> X; // Vector Roi rac hoa
int SIZE;
void update(int l, int r, const LINE& Line){
    update(1, 1, SIZE, l, r, Line);
}
pii query(int pos){
    return query(1, 1, SIZE, pos);
}
int LB(const int& val){
    return lower_bound(all(X), val) - X.begin();
}
int UB(const int& val){
    return upper_bound(all(X), val) - X.begin() - 1;
}

int f[maxn];
int tr[maxn];
void DP(){
    up(i,1,n){
        int cur = LB(x[i]);
        auto found = query(cur);
        f[i] = found.first + e[i];
        tr[i] = found.second;
        if (w[i] == 0) update(1, SIZE, {0ll, f[i], i});
        // never mess with binary search !!
        // this update mean "insert a line from -oo to oo with a = 0 and b = f[i]"
        // 0 = lower_bound(-oo);
        // SIZE = upper_bound(oo) - 1;
        else{
            int l = x[i] - f[i]/w[i];
            int r = x[i] + f[i]/w[i];
            update(LB(l), cur, {w[i], f[i] - w[i]*x[i], i});
            update(cur, UB(r), {-w[i], f[i] + w[i]*x[i], i});
        }
    }
}

void solve(){
    cin >> n;

    up(i,1,n){
        cin >> x[i] >> w[i] >> e[i];
        X.push_back(x[i]);
    }
    sort(all(X));
    purge(X);
    SIZE = X.size();
    nothing.set();

    X.insert(X.begin(), -1e9 - 7);
    X.push_back(1e9 + 7);
    up(i,1,SIZE) realval[i] = X[i];

    DP();

    int last = -1;
    int maxx = 0;
    up(i,1,n){
        if (maxx < f[i]){
            maxx = f[i];
            last = i;
        }
    }
    cout << maxx << "\n";

    vector<int> path;
    while (last != 0){
        path.ep(last);
        last = tr[last];
    }
    reverse(all(path));
    for (auto x : path) cout << x << " ";
}