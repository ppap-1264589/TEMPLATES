struct Knutt_Moris_Pratt{
    static const int maxn = 100001;
    int Pi[maxn];

    void make_KMP(string G){
        int n = G.size();
        int k = Pi[1] = 0;
        up(i,2,n){
            while (k && G[k+1] != G[i]) k = Pi[k];
            if (G[k+1] == G[i]) k++;
            Pi[i] = k;
        }
    }
    //Pi[x] computes the length of the longest prefix of s that ends at x

    int res[maxn];
    void count_occurence_prefix(string s){
        int n = s.size();
        make_KMP(s);
        fill(res+1, res+n+1, 1);
        down(i,n,1) res[Pi[i]] += res[i];
        up(i,1,n) cout << res[i] << " ";
    }

    void Find_Pattern(string s, string t){
        int n = s.size();
        int m = t.size();

        string g = '@' + t + '@' + s;
        make_KMP(g);

        up(i,1,n) if (Pi[i] == m) cout << i - 2*m << " ";
    }
} KMP;