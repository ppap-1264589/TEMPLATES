#define u64 unsigned long long
#define u128 __uint128_t
#define all(x) x.begin(), x.end()
#define ep emplace_back
mt19937_64 RNG(chrono::high_resolution_clock::now().time_since_epoch().count());
u64 UID(u64 l, u64 r){
    uniform_int_distribution<mt19937_64::result_type> random_number(l, r);
    return random_number(RNG);
}
struct FACTORS{
    const vector<u64> Milbase = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    u64 fpow(u64 x, u64 n, u64 M){
        u64 res = 1;
        for (; n; n >>= 1, x = (u128)x*x % M){
            if (n & 1) res = (u128)res*x % M;
        }
        return res;
    }

    bool divisible(u64 base, u64 cnt2, u64 d, u64 M){
        u64 extrem = fpow(base, d, M);
        if (extrem == 1 || extrem == M-1) return true;

        up(i,1,cnt2-1){
            extrem = (u128)extrem*extrem % M;
            if (extrem == M-1) return true;
        }
        return false;
    }

    bool MillerRabin(u64 n){
        if (n < 2) return false;

        u64 d = n-1;
        int cnt2 = 0;
        while ((d & 1) == 0){
            d >>= 1;
            ++cnt2;
        }

        for (auto base : Milbase){
            if (n == base) return true;
            if (n % base == 0) return false;
            if (!divisible(base, cnt2, d, n)) return false;
        }
        return true;
    }

    vector<u64> quickfact(int n){
        vector<u64> res;
        for (int i = 2; i*i <= n; i++){
            while (n % i == 0){
                n /= i;
                res.ep(i);
            }
        }
        if (n > 1) res.ep(n);
        return res;
    }

    const int C = 2;
    u64 f(u64 x, u64 MOD){
        return ((u128)x*x + C) % MOD;
    }

    u64 ABS(u64 x, u64 y){
        if (x > y) return x-y;
        return y-x;
    }

    u64 Brent(u64 n){
        u64 x,y,k,res;
        x = y = UID(2, n-1);
        k = 1;
        while (true){
            up(i,1,k){
                x = f(x, n);
                res = __gcd(ABS(x, y), n);
                if (res > 1) return res;
            }
            y = x;
            k <<= 1;
        }
        assert(false);
    }

    vector<u64> Pollard(u64 x){
        if (MillerRabin(x)) return {x};
        if (x <= 3e4) return quickfact(x);

        vector<u64> res;
        u64 p = Brent(x);
        vector<u64> L = Pollard(p);
        vector<u64> R = Pollard(x/p);
        res.insert(res.end(), all(L));
        res.insert(res.end(), all(R));
        return res;
    } //return prime factors of x in arbitrary order
} FACTS;