#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fbo(x) find_by_order(x)
#define ook(x) order_of_key(x)
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define down(i,a,b) for (int i = (int)a; i >= (int)b; i--)
#define int long long
#define all(x) x.begin(), x.end()
using namespace std;
using namespace __gnu_pbds;

tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update
> OMset;

void Add(int x){
    OMset.insert(x);
}

void Remove(int x){
    int pos = OMset.ook(x);
    auto it = OMset.fbo(pos);
    if (*it != x) return;
    OMset.erase(it);
}

string Minimum(){
    return (to_string)(*OMset.begin());
}

string Maximum(){
    return (to_string)(*OMset.rbegin());
}

string Succ(int x){ //least and > x
    auto it = OMset.upper_bound(x);
    if (it == OMset.end()) return "no";
    return (to_string)(*it);
}

string Succ2(int x){ //least and >= x
    auto it = OMset.lower_bound(x);
    if (it == OMset.end()) return "no";
    return (to_string)(*it);
}

string Pred(int x){ //most and < x
    auto it = OMset.lower_bound(x);
    if (it == OMset.begin()) return "no";
    return (to_string)(*--it);
}

string Pred2(int x){ //most and <= x
    auto it = OMset.upper_bound(x);
    if (it == OMset.begin()) return "no";
    return (to_string)(*--it);
}
