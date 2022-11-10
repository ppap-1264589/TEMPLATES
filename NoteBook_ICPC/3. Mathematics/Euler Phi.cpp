struct Euler_Phi{
    static const int maxn = 1e6 + 10;
    int phi[maxn];
    int n;
    void make_phi(int n) {
        for (int i = 1; i <= n; i++) phi[i] = i;
        for (int i = 2; i <= n; i++){
            if (phi[i] == i) {
                for (int j = i; j <= n; j += i) phi[j] -= phi[j] / i;
            }
        }
    }

    int eulerPhi(int n) {
        if (n == 0) return 0;
        int ans = n;
        for (int x = 2; x*x <= n; x++) {
            if (n % x == 0) {
                ans -= ans / x;
                while (n % x == 0) n /= x;
            }
        }
        if (n > 1) ans -= ans / n;
        return ans;
    }
} my_EP;