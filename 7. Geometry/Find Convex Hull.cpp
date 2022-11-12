static const int maxn = 2e5 + 10;
pii a[maxn];
pii R;
int n;

bool least(pii a, pii b){
    return (a.x < b.x || (a.x == b.x && a.y < b.y));
}

void in(){
    cin >> n;
    R.x = R.y = 2e9 + 1;
    up(i,1,n){
        cin >> a[i].x >> a[i].y;
        if (least(a[i], R)) R = a[i];
    }
}

pii Vect(pii a, pii b){
    return (make_pair(b.x - a.x, b.y - a.y));
}

long long CCW(pii a, pii b, pii c){
    pii u = Vect(a, b);
    pii v = Vect(b, c);
    return (1ll*u.x*v.y - 1ll*u.y*v.x);
}

bool counterclockwise(const pii& a, const pii& b){
    long long ccw = CCW(R, a, b);
    if (ccw == 0) return least(a, b);
    return ccw > 0;
}

int top = 0;
pii cv[maxn];
void find_convex(){
//        sort(a+1, a+n+1, counterclockwise);
    top = 1;
    cv[top] = R;

    for (int i = 2; i <= n; i++){
        while (top > 1 && CCW(cv[top-1], cv[top], a[i]) < 0) top--;
        cv[++top] = a[i];
    }
    pii endd = cv[top];
    for (int i = 2; i <= n; i++){
        if (a[i] != endd){
            if (CCW(R, a[i], endd) == 0) cv[++top] = a[i];
        }
    }
    cv[top+1] = R;
}

void PRINT(){
    cout << top << "\n";
    up(i,1,top){
        cout << cv[i].x << " " << cv[i].y << "\n";
    }
}