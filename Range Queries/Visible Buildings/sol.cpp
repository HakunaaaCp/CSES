/**
 *    author:  Hakunaaa
 *    created: 17.09.2025 15:00:13
**/
#include <bits/stdc++.h>
using namespace std;
 
const int LOG = 20, N = 1e5 + 1;
 
int p[N][LOG];
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> v(n + 1), t;
    for(int i = 1; i <= n; i++) cin >> v[i];
    for(int i = 0; i <= n; i++) for(int j = 0; j < LOG; j++) p[i][j] = 0;
    for(int i = n; i > 0; i--) {
        while(!t.empty() && v[t.back()] <= v[i]) t.pop_back();
        if(!t.empty()) p[i][0] = t.back();
        t.push_back(i);
    }
    for(int j = 1; j < LOG; j++) {
        for(int i = 1; i <= n; i++) {
            p[i][j] = p[p[i][j - 1]][j - 1];
        }
    }
    while(q--) {
        int l, r, cnt = 1; cin >> l >> r;
        while(l < r) {
            int i = 0;
            for(; ; i++) if(!p[l][i] || p[l][i] > r) break;
            if(!i) break;
            cnt += (1 << (i - 1));
            l = p[l][i - 1];
        }
        cout << cnt << '\n';
    } 
    return 0;
}