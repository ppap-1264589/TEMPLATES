#include <bits/stdc++.h>
#define up(i,a,b) for(int i = int(a); i <= int(b); i++)
#define down(i,a,b) for(int i = int(a); i >= int(b); i--)
#define Task "CHECK"
#define ep emplace_back
#define pii pair<int, int>
#define f first
#define s second
using namespace std;
typedef char NameFile[1000];

NameFile INP, OUT, ANS;
ifstream fi, fo, fa;

void Open_Files(){
    fi.open(INP);
    fo.open(OUT);
    fa.open(ANS);
}
void Close_Files(){
    fi.close();
    fo.close();
    fa.close();
}
void Define_Stream(){
    strcpy(ANS, INP);
    strcat(INP, Task".inp");
    strcat(OUT, Task".out");
    strcat(ANS, Task".out");
}

void Main_Checker();
signed main(){
    Define_Stream();
    Open_Files();

    Main_Checker();
    Close_Files();
}

bool Check_test(){

}

void Main_Checker(){
    bool result = Check_test();
    cout << "\n";
    cout << (result ? 1.00 : 0.00);
}
