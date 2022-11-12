struct MANACHER{
    static const int maxn = 1e6 + 10;
    string s;
    int d1[maxn];
    int d2[maxn];
    int pos = -1;
    int maxx = -1;
    int n;

    void Manachers_Odd(){
        for (int l = 1, r = 0, i = 1; i <= n; i++){
            int k = (i > r) ? 1 : min(d1[l+r-i], r - i + 1);
            while (i-k >= 1 && i+k <= n && s[i-k] == s[i+k]) k++;

            d1[i] = k--;
            if (maxx < d1[i]*2-1){
                maxx = d1[i]*2-1;
                pos = i - d1[i] + 1;
            }
            if (i + k > r){
                r = i + k;
                l = i - k;
            }
        }
    }

    void Manachers_Even(){
        for (int l = 1, r = 0, i = 2; i <= n; i++){
            int k = (i > r) ? 0 : min(d2[l+r-i], r - i + 1);
            while (i-k-1 >= 1 && i+k <= n && s[i-k-1] == s[i+k]) k++;

            d2[i] = k--;
            if (maxx < d2[i]*2){
                maxx = d2[i]*2;
                pos = i - d2[i];
            }
            if (i + k > r){
                r = i + k;
                l = i - k;
            }
        }
    }

    void solve(){
        cin >> n;
        cin >> s;

        s = '@' + s;
        Manachers_Odd();
        Manachers_Even();
        cout << maxx;
    }
} my_manacher;