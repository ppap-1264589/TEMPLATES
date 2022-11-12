const int maxn = 5e3 + 10;
int n,m;
pii a[maxn];

int Sign(long long x){
    if (x < 0) return -1;
    if (x > 0) return 1;
    return 0;
}

pii Vect(pii p, pii q){
    return make_pair(q.x - p.x, q.y - p.y);
}

long long CCW(pii u, pii v){
    return Sign(1ll*u.x*v.y - 1ll*u.y*v.x);
}

bool same_spin(pii root, pii u, pii v){
    return (CCW(root, u)*CCW(root, v) > 0);
}

bool diff_spin(pii root, pii u, pii v){
    return (CCW(root, u)*CCW(root, v) < 0);
}

bool in_convexhull(pii K){
    pii VL = Vect(a[1], a[2]);
    pii VR = Vect(a[1], a[n]);
    pii VT = Vect(a[1], K);
    if (!same_spin(VL, VR, VT)) return 0;
    if (!same_spin(VR, VL, VT)) return 0;

    int L = 2;
    int R = n;
    while (R - L > 1){
        int mid = (L+R) >> 1;
        if (same_spin(Vect(a[1], a[mid]), VT, VL)) R = mid;
        else L = mid;
    }

    pii UL = Vect(a[L], a[1]);
    pii UR = Vect(a[L], a[R]);
    pii UT = Vect(a[L], K);
    if (diff_spin(UL, UR, UT)) return 0;
    if (diff_spin(UR, UL, UT)) return 0;
    if (CCW(UR, UT) == 0) return 0;
    // Quick understand : There is the only case that the algorithm will fail after found the triangle contain the point in the polygon
    return 1;
}

void solve(){
    cin >> n;
    up(i,1,n) cin >> a[i].x >> a[i].y;
    cin >> m;
    up(i,1,m){
        pii K;
        cin >> K.x >> K.y;
        if (in_convexhull(K)) cout << "YES";
        else cout << "NO";
        cout << "\n";
    }
}