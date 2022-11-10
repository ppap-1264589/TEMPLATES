struct IT_Duong_Thang{
    static const int maxn = 1e6 + 10;
    static const int MOD = 2e9 + 11;
    int n;
    struct Line{
        int a,b,pos;
    };
    Line a[maxn];
    Line it[maxn << 2];

    void build(int nod, int l, int r){
        it[nod] = {0, MOD, 0};
        if (l == r) return;
        int mid = (l+r) >> 1;
        build(nod*2, l, mid);
        build(nod*2+1, mid+1, r);
    }

    long long get(Line L, int x){
        return 1ll*x*L.a + L.b;
    }

    void update(int nod, int l, int r, Line val){
        int mid = (l + r) >> 1;
        bool aboveLeft = (get(it[nod], l) > get(val, l));
        bool aboveMid = (get(it[nod], mid) > get(val, mid));
        if (aboveMid) swap(val, it[nod]);
        if (l == r) return;
        if (aboveLeft != aboveMid) update(nod*2, l, mid, val);
        else update(nod*2+1, mid+1, r, val);
    }

    void add(Line L){
        update(1, -maxn, maxn, L);
    }

    Line query(int nod, int l, int r, int x){
        if (l == r) return it[nod];
        int mid = (l + r) >> 1;
        if (x <= mid){
            Line L = query(nod*2, l, mid, x);
            if (get(it[nod], x) < get(L, x)) return it[nod];
            return L;
        }
        Line R = query(nod*2+1, mid+1, r, x);
        if (get(it[nod], x) < get(R, x)) return it[nod];
        return R;
    }

    Line _query(int k){
        return query(1, -maxn, maxn, k);
    }

    void solve(){
        build(1, -maxn, maxn);
        cin >> n;
        up(i,1,n){
            cin >> a[i].a >> a[i].b;
            a[i].pos = i;
            add(a[i]);
        }

        int q;
        cin >> q;
        while (q--){
            int k;
            cin >> k;
            Line res = _query(k);
            cout << get(res, k) << "\n";
        }
    }
} my_IT_Duong_Thang;