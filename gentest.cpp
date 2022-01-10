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
#define pii pair<int, int>
#define f first
#define s second
#define MP make_pair
#define ep emplace_back
#define bit(x, i) (((x) >> (i)) & 1)
#define all(x) x.begin(), x.end()
#define isTLE (1.0*clock()/CLOCKS_PER_SEC > 0.95)
#define MAX_ARR_SIZE 486010000
#define int long long
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







/** --------------- Define Random Generation --------------- **/
mt19937 RNG(chrono::high_resolution_clock::now().time_since_epoch().count());
int UID(int l, int r){
    uniform_int_distribution<mt19937::result_type> random_number(l, r);
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
char NAME_file[] = "SORTING";  // <- Enter your "Task name" here
char exe_file[100] = "CHECKER"; // <= Enter your "Checker name" here
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




/** ----------------- Main Processes ------------------ **/
void prepare_test(){

}

void detail_test(int& test){
    fo << UID(1, 1000);
}

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
