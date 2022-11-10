struct Mo_Algorithm{
    static const int maxn = 1e5 + 10;
    static const int maxq = 5e5 + 10;
    static const int BLOCK = 512; //should be (1 << 9)
    int n,q;

    struct Query{
        int l,r,id;
        Query(){}
        Query(int l, int r, int id):
            l(l), r(r), id(id)
        {}

        bool operator < (const Query& O) const {
            if (l/BLOCK != O.l/BLOCK) return l < O.l;
            return (l/BLOCK & 1 ? r < O.r : r > O.r);
        }
    } Q[maxq];

    struct Counter{
        void add(int x){}

        void sub(int pos){}

        int query(){ return 0; }
    } MO;

    int ans[maxq];

    void solve(){
        cin >> n >> q;

        //do somthing with n here

        up(i,1,q){
            int l,r;
            cin >> l >> r;
            Q[i].l = l;
            Q[i].r = r;
            Q[i].id = i;
        }
        sort(Q+1, Q+q+1);

        int cl = 1;
        int cr = 0;
        up(i,1,q){
            int l = Q[i].l;
            int r = Q[i].r;
            int id = Q[i].id;
            while (cl > l) MO.add(--cl);
            while (cl < l) MO.sub(cl++);
            while (cr > r) MO.sub(cr--);
            while (cr < r) MO.add(++cr);
            ans[id] = MO.query();
        }

        up(i,1,q) cout << ans[i] << "\n";
    }
} My_MO;