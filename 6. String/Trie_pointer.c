#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)

typedef struct Trie Trie;
struct Trie{
    Trie *child[27];
    char data;
    int pref;
    int exist;
};

Trie *ROOT;

Trie *CreateNode(char data){
    Trie *node = (Trie*)malloc(1 * sizeof(Trie));  //Cap bo nho cho con tro node kieu Trie
    up(i,0,26) node->child[i] = NULL;
    node->data = data;
    node->pref = 0;
    node->exist = 0;
    return node;
}

void FreeNode(Trie *node){ //DFS
    up(i,0,26){
        if (node->child[i] != NULL){
            FreeNode(node->child[i]);
        }
    }
    free(node);
}

void Insert(Trie *root, char *word){
    Trie *cur = root;
    for (int i = 0; word[i] != '\0'; i++){
        int id = word[i] - 'a';
        if (cur->child[id] == NULL){ //Chi chen them khi khong tim thay node da co trong Trie
            cur->child[id] = CreateNode(word[i]);
        }
        cur = cur->child[id];
        ++cur->pref;
    }
    ++cur->exist;
}

bool Find(Trie *root, char *word){
    Trie *cur = root;
    for (int i = 0; word[i] != '\0'; i++){
        int id = word[i] - 'a';
        if (cur->child[id] == NULL) return 0; //Chac chan khong tim thay neu chay ra ngoai cac node da biet
        cur = cur->child[id];
    }
    return cur->exist;
}

bool Remove(Trie *cur, char *word, int pos){
    if (word[pos] != '\0'){
        int id = word[pos] - 'a';
        bool isChildRemoved = Remove(cur->child[id], word, pos+1);
        if (isChildRemoved) cur->child[id] = NULL;
    }
    else --cur->exist; //Cuoi tu

    if (cur != ROOT){ //Dam bao khong free(ROOT)
        --cur->pref;
        if (cur->pref == 0){
            free(cur);
            return true;
        }
    }
    return false;
}

void Undo(Trie *T, char* word){
    if (Find(T, word) == 0){
        printf("WORD NOT FOUND IN DICTIONARY !\n");
        exit(0);
    }
    Remove(T, word, 0);
}

int n,q;
char s[201];
char t[201];

signed main(){
    #define Task "A"
    if (fopen(Task".inp", "r")){
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    ROOT = CreateNode('\0'); //Default node

    Trie *T;
    T = CreateNode('\0');

    scanf("%d", &n);
    up(i,1,n){
        scanf("%s", s);
        Insert(T, s);
    }

    scanf("%d", &q);
    up(i,1,q){
        int type;
        scanf("%d", &type);
        scanf("%s", s);
        if (type == 1) Insert(T, s);
        if (type == 2) printf("%d\n", Find(T, s));
        if (type == 3) Undo(T, s);
    }

    FreeNode(ROOT);
    FreeNode(T);
}
