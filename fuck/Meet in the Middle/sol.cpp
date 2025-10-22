/**
 *    author:  Hakunaaa
 *    created: 22.10.2025 22:24:56
**/
#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, sum; cin >> n >> sum;
    vector<int> v(n), t[2];
    for(int &el : v) cin >> el;
    for(int it = 0; it < 2; it++) {
        int l = (it ? (n + 1) / 2 : n / 2);
        for(int i = 0; i < (1 << l); i++) {
            int s = 0;
            for(int j = 0; j < l; j++) {
                if(i >> j & 1) s += v[n / 2 * it + j];
            }
            t[it].push_back(s);
        }
    }
    for(int i = 0; i < 2; i++) sort(t[i].begin(), t[i].end());
    auto find = [&](int val) -> int {
        int l = 0, r = t[1].size() - 1;
        while(l < r) {
            int m = (l + r) / 2;
            if(t[1][m] < val) l = m + 1;
            else r = m;
        }
        if(t[1][l] != val) return 0;
        int p = l;
        l = 0, r = t[1].size() - 1;
        while(l < r) {
            int m = (l + r + 1) / 2;
            if(t[1][m] > val) r = m - 1;
            else l = m;
        }
        return l - p + 1;
    };
    int ans = 0;
    for(int el : t[0]) ans += find(sum - el);
    cout << ans;
    return 0;
}