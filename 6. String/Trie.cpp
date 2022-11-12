struct Trie{
    static const int maxn = 1000001;

    struct nod{
        int child[27];
        bool IE;
    };

    struct nod T[maxn];
    int n,m,depth;

    void Add(string s){
        int x = 0; // root;
        for (char c : s){
            int id = c - 'a' + 1;
            if (T[x].child[id] == 0) T[x].child[id] = ++depth;
            x = T[x].child[id];
        }
        T[x].IE = 1;
    }

    bool Find(string s){
        int x = 0;
        for (char c : s){
            int id = c - 'a' + 1;
            if (T[x].child[id] == 0) return 0;
            x = T[x].child[id];
        }
        return T[x].IE;
    }
} TRIE;