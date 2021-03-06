/** --------------- Define code Shortcuts --------------- **/
//Hoang1264589
//#pragma GCC optimize("O2")
//#pragma GCC optimize ("unroll-loops")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include "bits/stdc++.h"
#include "windows.h"
#include "direct.h"
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define down(i,a,b) for (int i = (int)a; i >= (int)b; i--)
#define pii pair<long long, long long>
#define x first
#define y second
#define MP make_pair
#define ep emplace_back
#define bit(x, i) (((x) >> (i)) & 1)
#define all(x) x.begin(), x.end()
#define isTLE (1.0*clock()/CLOCKS_PER_SEC > 0.95)
#define MAX_ARR_SIZE 486010000
#define int long long
#define PI 3.14159265359
using namespace std;
const int MOD = 1e9 + 7;




/** --------------- Define Random Generation --------------- **/
mt19937 RNG(chrono::high_resolution_clock::now().time_since_epoch().count());
int UID(int l, int r){
    uniform_int_distribution<int> random_number(l, r);
    return random_number(RNG);
}

template<class Iter>
Iter FisherYates(Iter Begin, Iter End, size_t choose) {
    size_t left = distance(Begin, End);
    while (choose--) {
        int RD = UID(1, 1000000007);
        Iter r = Begin;
        advance(r, RD%left);
        swap(*Begin, *r);
        ++Begin, --left;
    }
    return Begin;
}
vector<int> pick_shuffle(vector<int>& temp, int choose){
    vector<int> res;
    FisherYates(temp.begin(), temp.end(), choose);
    up(i,0,choose-1) res.ep(temp[i]);
    return res;
}







/** --------------- Define Folder names --------------- **/
int maxtest;
bool return_test;
ofstream fo;
ofstream rfo("DRAFT.out");  // <- table of contents of testcases
ofstream afo("A.out");
char NAME_file[] = "";  // <- Enter your "Task name" here
char exe_file[100] = ""; // <= Enter your "Checker name" here
char inp_file[100] = "";
char out_file[100] = "";
string folder = "Test000";


/** ----------------- Define File Behaviour ------------------ **/
void Rename_file(int test){
    folder[4] = test/100 + '0';
    folder[5] = test/10%10 + '0';
    folder[6] = test%10 + '0';
}

void Redirect_folder(){
    mkdir(&folder[0]);
    string output_path = folder + "\\" + inp_file;
    CopyFile(inp_file, &output_path[0], false);
    output_path = folder + "\\" + out_file;
    CopyFile(out_file, &output_path[0], false);
}

void Make_file_name(){
    strcpy(inp_file, NAME_file);
    strcpy(out_file, NAME_file);

    strcat(inp_file, ".inp");
    strcat(out_file, ".out");
}




/** ----------------- Default Random Algorithm ------------------ **/
namespace ConvexHull{ // Stolen from https://cglab.ca/~sander/misc/ConvexGeneration/convex.html
    const double eps = 1e-9;
    bool comp_angle(const pii& X, const pii& Y){
        double A1 = atan2(X.y, X.x);
        double A2 = atan2(Y.y, Y.x);
        return (A1 + eps < A2);
    }

    vector<int> x_init;
    vector<int> y_init;
    void random_points(int n, int MINX, int MAXX, int MINY, int MAXY){
        up(i,1,n){
            int x = UID(MINX, MAXX);
            int y = UID(MINY, MAXY);
            x_init.ep(x);
            y_init.ep(y);
        }
    }

    vector<int> Xcoor;
    vector<int> Ycoor;
    int minX, minY, maxX, maxY;

    vector<int> to_vect_coor(vector<int>& COOR, int MIN, int MAX){
        vector<int> res;
        int lastmin, lastmax;
        lastmin = lastmax = MIN;
        up(i,1,COOR.size()-2){
            int p = COOR[i];
            if (UID(0, 1)){
                res.ep(p - lastmin);
                lastmin = p;
            }
            else {
                res.ep(lastmax - p);
                lastmax = p;
            }
        }
        res.ep(MAX - lastmin);
        res.ep(lastmax - MAX);
        return res;
    }

    void random_convex_vector(){
        sort(all(x_init));
        sort(all(y_init));
        minX = *x_init.begin();
        maxX = *x_init.rbegin();
        minY = *y_init.begin();
        maxY = *y_init.rbegin();

        Xcoor = to_vect_coor(x_init, minX, maxX);
        Ycoor = to_vect_coor(y_init, minY, maxY);
        shuffle(all(Ycoor), RNG);
    }


    int sumx, sumy;
    int minpolyX, minpolyY;
    vector<pii> convex;
    void Consecutive_generate(int n){
        vector<pii> V;
        up(i,1,n) V.push_back(make_pair(Xcoor[i-1], Ycoor[i-1]));
        sort(all(V), comp_angle);

        for (auto p : V){
            convex.push_back(make_pair(sumx, sumy));
            sumx += p.x;
            sumy += p.y;
            minpolyX = min(minpolyX, sumx);
            minpolyY = min(minpolyY, sumy);
        }
    }

    void shift_hull_back(){
        int xShift = minX - minpolyX;
        int yShift = minY - minpolyY;

        pii Root = make_pair(1e18, 1e18);
        for (auto& p : convex){
            p.x += xShift;
            p.y += yShift;
            Root = min(Root, make_pair(p.x, p.y));
        }
        while (convex.front() != Root){
            pii k = convex.front();
            convex.erase(convex.begin());
            convex.push_back(k);
        }
    }

    void clear_data(){
        x_init.clear();
        y_init.clear();
        Xcoor.clear();
        Ycoor.clear();
        convex.clear();
    }

    vector<pii> random_convex_hull(int n, int MINX, int MAXX, int MINY, int MAXY){
        clear_data();
        random_points(n, MINX, MAXX, MINY, MAXY);
        random_convex_vector();
        Consecutive_generate(n);
        shift_hull_back();
        return convex;
    }
}

namespace Array{
    vector<int> random_array(int len, int Llim, int Rlim){
        vector<int> a;
        a.ep(0);
        for (int i = 1; i <= len; i ++) a.ep(UID(Llim, Rlim));
        return a;
    }

    vector<vector<int>> random_matrix(int row, int col, int Llim, int Rlim){
        vector<vector<int>> a;
        a.resize(row + 5);
        for (int i = 1; i <= col; i ++) a[i] = random_array(col, Llim, Rlim);
        return a;
    }
}

struct edge{
    int u,v,w;
};
namespace Graph{
    ///Random tree (stolen from Nguyen Duc Kien)
    vector<pii> random_tree(int num_node){
        vector<pii> G;
        for (int i = 2; i <= num_node; i ++){
            int j = UID(1, i-1);
            G.ep(i, j);
        }
        shuffle(all(G), RNG);
        return G;
    }

    vector<pii> random_line_tree(int num_node, int root){
        vector<pii> G;
        vector<int> p;
        p.resize(num_node + 10);
        up(i,1,num_node) p[i] = i;
        swap(p[root], p[1]);
        shuffle(p.begin()+2, p.begin()+num_node+1, RNG);

        up(i,2,num_node){
            int x = p[i];
            int y = p[i-1];
            int seed = UID(0, 1);
            if (seed) swap(x, y);
            G.ep(x, y);
        }
        shuffle(all(G), RNG);
        return G;
    }

    vector<edge> random_w_tree(int num_node, int L_wLIM, int R_wLIM){
        vector<edge> G;
        for (int i = 2; i <= num_node; i ++){
            int j = UID(1, i-1);
            int w = UID(L_wLIM, R_wLIM);
            G.push_back({i, j, w});
        }
        shuffle(all(G), RNG);
        return G;
    }

    ///Random graph (stolen from Nguyen Duc Kien)
    vector<pii> random_graph(int num_node, int num_edge){
        vector<pii> G = random_tree(num_node);
        num_edge -= num_node - 1;
        if(num_node <= 4000){
            vector<vector<int>> m(num_node + 1, vector<int>(num_node + 1));
            vector<pii> q;
            for(auto e : G) m[e.first][e.second] = m[e.second][e.first] = 1;
            up(i, 1, num_node) up(j, i+1, num_node) if (!m[i][j]) q.ep(i,j);

            shuffle(all(q), RNG);
            for(int i = 0; i < num_edge; i++){
                int type = UID(0,1);
                if (type) G.ep(q[i].first, q[i].second);
                else G.ep(q[i].second, q[i].first);
            }
        }
        else{
            map<pii ,bool> m;
            for (auto e : G) m[e] = m[{e.second, e.first}] = 1;
            for(int i = 0; i < num_edge; i++){
                int u = UID(1, num_node);
                int v = UID(1, num_node);
                while (u == v | m[{u,v}]) v = UID(1, num_node), u = UID(1, num_node);
                m[{u,v}] = m[{v,u}] = 1;
                G.ep(u, v);
            }
        }
        shuffle(all(G), RNG);
        return G;
    }

    vector<edge> random_w_graph(int num_node, int num_edge, int Lw, int Rw){
        vector<edge> G = random_w_tree(num_node, Lw, Rw);
        num_edge -= num_node - 1;
        if(num_node <= 4000){
            vector<vector<int>> m(num_node + 1, vector<int>(num_node + 1));
            vector<pii> q;
            for (auto e : G) m[e.u][e.v] = m[e.v][e.u] = 1;
            up(i, 1, num_node) up(j, i+1, num_node) if (!m[i][j]) q.ep(i, j);

            shuffle(all(q), RNG);
            for(int i = 0; i < num_edge; i++){
                int type = UID(0,1);
                int w = UID(Lw, Rw);
                if (type) G.push_back({q[i].first, q[i].second, w});
                else G.push_back({q[i].second, q[i].first, w});
            }
        }
        else{
            map<pii ,bool> m;
            for (auto e : G) m[{e.u, e.v}] = m[{e.v, e.u}] = 1;
            for(int i = 0; i < num_edge; i++){
                int u = UID(1, num_node);
                int v = UID(1, num_node);

                while (u == v || m[{u,v}]) v = UID(1, num_node), u = UID(1, num_node);
                m[{u,v}] = m[{v,u}] = 1;
                int w = UID(Lw, Rw);
                G.push_back({u, v, w});
            }
        }
        shuffle(all(G), RNG);
        return G;
    }
}

namespace String{
    string random_string(int n, int have_digit, int have_upper, int have_lower){
        if ((have_digit || have_upper || have_lower) == 0) return "";
        string res = "";
        vector<int> state;
        if (have_digit) state.ep(0);
        if (have_upper) state.ep(1);
        if (have_lower) state.ep(2);
        for (auto x : state) afo << x << "\n";
        up(i,1,n){
            int type = UID(0, (int)state.size() - 1);
            int k = state[type];
            if (k == 0) res += char(UID(1, 1000000000) % 10 + '0');
            if (k == 1) res += char(UID(1, 1000000000) % 26 + 'A');
            if (k == 2) res += char(UID(1, 1000000000) % 26 + 'a');
        }
        return res;
    }
}



/** ----------------- Opening and Closing Files ------------------ **/
void prepare_test();
void detail_test(int& test);
void generate_test(){
    prepare_test();
    Make_file_name();
    up(test, 1, maxtest){
        return_test = 0;
        fo.open(inp_file);
        detail_test(test);
        if (return_test == 1) {
            fo.close();
            continue;
        }
        fo.close();
        system(exe_file);
        Rename_file(test);
        Redirect_folder();
    }
    DeleteFile(inp_file);
    DeleteFile(out_file);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    maxtest = 1;
    generate_test();
}




using namespace ConvexHull;
using namespace Array;
using namespace Graph;
using namespace String;

/** ----------------- Main Generation ------------------ **/
void prepare_test(){

}

void detail_test(int& test){

}
