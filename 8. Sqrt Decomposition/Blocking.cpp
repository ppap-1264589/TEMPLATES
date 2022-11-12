struct Blocker{
    static const int maxn = 1e5 + 10;
    int Bsize;
    multiset<int> BLOCK[maxn];
    int Lblock[maxn], Rblock[maxn];
    int n,q;
    int a[maxn];

    int getblock(const int& pos){
        return (pos + Bsize - 1)/Bsize;
    }

    void divide(){
        int lastblock = getblock(n);
        up(i,1,n){
            int cur = getblock(i);
            BLOCK[cur].insert(a[i]);

            if (cur == lastblock){
                Lblock[i] = (lastblock-1)*Bsize+1;
                Rblock[i] = n;
            }
            else{
                Rblock[i] = min(n, cur*Bsize);
                Lblock[i] = Rblock[i] - Bsize + 1;
            }
        }
    }

    void update(int pos, int val){
        int curblock = getblock(pos);
        auto it = BLOCK[curblock].find(a[pos]);
        BLOCK[curblock].erase(it);
        BLOCK[curblock].insert(val);
        a[pos] = val;
    }

    int query(int l, int r, int k){
        int L = getblock(l);
        int R = getblock(r);

        int minn = 1e9 + 7;
        if (L == R){
            up(i,l,r){
                if (a[i] >= k) minn = min(minn, a[i]);
            }
            return (minn == 1e9 + 7 ? -1 : minn);
        }

        for (int i = l; i <= Rblock[l]; i++){
            if (a[i] >= k) minn = min(minn, a[i]);
        }
        for (int i = Lblock[r]; i <= r; i++){
            if (a[i] >= k) minn = min(minn, a[i]);
        }
        for (int i = L+1; i <= R-1; i++){
            auto it = BLOCK[i].lower_bound(k);
            if (*it >= k) minn = min(minn, *it);
        }
        return (minn == 1e9 + 7 ? -1 : minn);
    }

    void solve(){
        cin >> n >> q;
        up(i,1,n) cin >> a[i];
        Bsize = sqrt(n);
        divide();

        up(i,1,q){
            int type;
            int l,r;
            int pos,val;
            cin >> type;
            if (type == 1){
                cin >> pos >> val;
                update(pos, val);
            }
            else {
                cin >> l >> r >> val;
                cout << query(l, r, val) << "\n";
            }
        }
    }
} my_Blocker; //find the lower_bound(k) in range [l, r]