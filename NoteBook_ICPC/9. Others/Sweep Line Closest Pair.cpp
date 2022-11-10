long long ClosestPair(vector<pair<int, int> > p) {
    int n = p.size();
    sort(p.begin(), p.end());
    set<pair<int, int>> S;

    long long best_dist = 1e18;
    int j = 0;
    for (int i = 0; i < n; i++) {
        int d = ceil(sqrt(best_dist));
        while (p[i].first - p[j].first >= d && j < n) {
            S.erase({p[j].second, p[j].first});
            ++j;
        }

        auto it1 = S.lower_bound({p[i].second - d, p[i].first});
        auto it2 = S.upper_bound({p[i].second + d, p[i].first});

        for (auto it = it1; it != it2; ++it) {
            int dx = p[i].first - it->second;
            int dy = p[i].second - it->first;
            best_dist = min(best_dist, 1ll*dx*dx + 1ll*dy*dy);
        }
        S.insert({p[i].second, p[i].first});
    }
    return best_dist;
}