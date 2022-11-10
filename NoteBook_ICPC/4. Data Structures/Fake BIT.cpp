struct FakeUpdate_FakeGet{
    const int maxn = 1e5 + 10;
    int n;
    vector<int> a,b;
    vector<int> BIT[maxn];
    vector<int> node[maxn];

    void fakeupdate(int x, int yy){
        for (; x; x -= (x & (-x))){
            node[x].ep(yy);
        }
    }
    void fakeget(int x, int yy){
        for (; x <= n+1; x += (x & (-x))){
            node[x].ep(yy);
        }
    }
    void update(int x, int yy, int val){
        for (; x; x -= (x & (-x))){
            for (int y = LB(node[x], yy)+1; y; y -= (y & (-y))){
                BIT[x][y] = max(BIT[x][y], val);
            }
        }
    }
    int get(int x, int yy){
        int res = 0;
        for (; x <= n+1; x += (x & (-x))){
            for (int y = LB(node[x], yy)+1; y <= (int)node[x].size(); y += (y & (-y))){
                res = max(res, BIT[x][y]);
            }
        }
        return res;
    }

    void compress(vector<int>& a){
        vector<int> Val = a;
        sort(all(Val));
        purge(Val);
        for (auto& x : a){
            x = LB(Val, x) + 2;
        }
    }

    void input(){
        cin >> n;
        up(i,1,n){
            int x,y;
            cin >> x >> y;
            a.ep(x);
            b.ep(y);
        }
    }

    void init(){
        compress(a);
        compress(b);
        a.insert(a.begin(), -1);
        b.insert(b.begin(), -1);
        up(i,1,n){
            fakeupdate(a[i], b[i]);
            fakeget(a[i]+1, b[i]+1);
        }
        up(i,1,n+2){
            sort(all(node[i]));
            purge(node[i]);
            BIT[i].resize(node[i].size()+5);
        }
    }

    void solve(){
        input();
        init();
        ///do something
    }
} Fake_BIT;