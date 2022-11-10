const int maxn = 1e5 + 10;
int n,m;
pii P[maxn];
pii K;

int sign(long long k){
    if (k < 0) return -1;
    if (k > 0) return 1;
    return 0;
}

pii vect(pii p, pii q){
    return make_pair(q.x - p.x, q.y - p.y);
}

long long dot(pii u, pii v){
    long long DOT = u.x*v.x + u.y*v.y;
    return sign(DOT);
}

long long cross(pii u, pii v){
    long long ccw = u.x*v.y - u.y*v.x;
    return sign(ccw);
}

int intersect(pii A, pii C, pii D){
    int ACD = cross(vect(A, C), vect(C, D));
    int CDA = cross(vect(C, D), vect(D, A));

    if (CDA == 0 && dot(vect(A, D), vect(A, C)) <= 0) return 1;

    if (C.y <= A.y && D.y > A.y && ACD < 0) return 2;
    if (C.y > A.y && D.y <= A.y && ACD > 0) return 2;
    return 0;
}

string Point_in_Polygon(){
    int cnt = 0;
    bool boundary = 0;
    up(i,1,n){
        pii cur = P[i];
        pii next = P[i+1];
        if (intersect(K, cur, next) == 1){
            boundary = 1;
            break;
        }
        if (intersect(K, cur, next) == 2) ++cnt;
    }
    if (boundary) return "BOUNDARY";
    else if (cnt & 1) return "INSIDE";
    return "OUTSIDE";
}

void solve(){
    cin >> n >> m;
    up(i,1,n) cin >> P[i].x >> P[i].y;
    P[n+1] = P[1];
    up(i,1,m){
        cin >> K.x >> K.y;
        cout << Point_in_Polygon() << "\n";
    }
}