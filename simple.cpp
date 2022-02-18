//Hoang1264589
//#pragma GCC optimize("O2")
//#pragma GCC optimize ("unroll-loops")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include "bits/stdc++.h"
#define Task "A"
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define down(i,a,b) for (int i = (int)a; i >= (int)b; i--)
#define pii pair<int, int>
#define f first
#define s second
#define MP make_pair
#define ep emplace_back
#define all(x) x.begin(), x.end()
#define bit(x,i) ((x >> i) & 1)
#define MAX_ARR_SIZE 486010000
#define isTLE (1.0*clock()/CLOCKS_PER_SEC > 0.95)
#define overbit(i, type, MASK, x) for (int i = (type == 1 ? x : (MASK-1)^x); i > 0; i ^= (i & -i))
using namespace std;
const int MOD = 1e9 + 7;

template<class X, class Y>
bool Minim(X &x, const Y &y) {
    X eps = 1e-9;
    return (x > y + eps ? (x = y) : 0);
}
template<class X, class Y>
bool Maxim(X &x, const Y &y) {
    X eps = 1e-9;
    return (x < y - eps ? (x = y) : 0);
}



signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    if (fopen(Task".inp", "r")){
        freopen (Task".inp", "r", stdin);
        freopen (Task".out", "w", stdout);
    }

    return 0;
}
