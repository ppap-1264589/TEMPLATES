#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Trie Trie;

struct Trie{ //tru cho struct Trie nay ra, cac tu Trie con lai, deu duoc hieu la (struct Trie)
    char data;
    Trie *child[27];
    int cnt;
};

Trie *New_node(char data){
    //allocate memory for a Trie
    Trie node = (Trie)calloc(1, sizeof(Trie));
    for (int i = 0; i < 26; i++){
        node->child[i] = NULL;
    }
    node->cnt = 0;
    node->data = data;
    return node;
};

void Free_node(Trie *node){
    //first, free the node in tree
    for (int i = 0; i < 26; i++){
        if (node->child[i] != NULL){
            Free_node(node->child[i]);
        }
    }
    //then, free the whole pointer
    free(node);
}

void Insert(Trie *root, char *word){
    Trie *cur = root;
    for (int i = 0; i < strlen(word); i++){
        int id = word[i] - 'a';
        if (cur->child[id] == NULL){ //Chi tao node moi khi khong tim duoc child ke tiep
            cur->child[id] = New_node(word[i]);
        }
        cur = cur->child[id];
        ++cur->cnt;
    }
}

int Count(Trie *root, char *word){
    Trie *cur = root;
    for (int i = 0; i < strlen(word); i++){
        int id = word[i] - 'a';
        if (cur->child[id] == NULL) return 0; //Ngay khi cham den mot node khong ton tai -> khong tim thay tu do
        cur = cur->child[id];
    }
    return cur->cnt;
}

void Remove(Trie *root, char *word){
    if (root == NULL) return;
    if (word[0] == '\0'){
        --root->cnt;
        return;
    }

    int id = word[0] - 'a';
    Remove(root->child[id], word+1);

    if (root->child[id] == NULL && root->cnt == 0){
        free(root);
        root = NULL;
    }
}

char s[101];
int n,m;

int main(){
    #define Task "A"
    if (fopen(Task".inp", "r")){
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

    Trie *T = New_node('\0');

    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%s", s);
        Insert(T, s);
    }

    scanf("%d", &m);
    for (int i = 1; i <= m; i++){
        scanf("%s", s);
        printf("%d\n", Count(T, s));
    }

	Free_node(T);
}
