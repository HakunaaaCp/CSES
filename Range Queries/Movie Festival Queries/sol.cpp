/**
 *    author:  Hakunaaa
 *    created: 18.09.2025 22:26:11
**/
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1, LOG = 19;
int dp[N][LOG];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q; cin >> n >> q;
    // init
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < LOG; j++) {
            dp[i][j] = -1;
        }
    }
    vector<array<int, 2>> v(n), t;
    for(auto &[f, s] : v) cin >> f >> s;
    sort(v.begin(), v.end());
    t.push_back(v[0]);
    for(int i = 1; i < n; i++) {
        if(v[i][0] == (t.back())[0]) continue;
        while(!t.empty() && (t.back())[1] >= v[i][1]) t.pop_back();
        t.push_back(v[i]);
    }
    v = t;
    n = v.size();
    for(int i = 0; i < n; i++) {
        int l = i + 1, r = n - 1;
        while(l < r) {
            int m = (l + r) / 2;
            if(v[m][0] < v[i][1]) l = m + 1;
            else r = m;
        }
        if(v[i][1] <= v[l][0]) dp[i][0] = l;
    }    
    for(int j = 1; j < LOG; j++) {
        for(int i = 0; i < n; i++) {
            if(dp[i][j - 1] != -1) dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
    while(q--) {
        int a, b; cin >> a >> b;
        int l = 0, r = n - 1;
        while(l < r) {
            int m = (l + r) / 2;
            if(v[m][0] >= a) r = m;
            else l = m + 1;
        }
        if(v[l][0] < a || v[l][1] > b) cout << 0;
        else {
            int ans = 1;
            while(t[l][1] <= b) {
                int i = 0;
                for(; ; i++) {
                    int p = dp[l][i];
                    if(p == -1 || v[p][1] > b) break;
                }
                if(!i) break;
                ans += (1 << (i - 1));
                l = dp[l][i - 1];
            }
            cout << ans;
        }
        cout << '\n';
    }
    return 0;
}