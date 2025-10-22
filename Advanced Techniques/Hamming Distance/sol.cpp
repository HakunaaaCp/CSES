/**
 *    author:  Hakunaaa
 *    created: 22.10.2025 22:47:02
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        int cur = 0;
        for(char c : s) cur = cur * 2 + (c == '1');
        v[i] = cur; 
    }
    int ans = 1e9;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            ans = min(ans, __builtin_popcount(v[i] ^ v[j]));
        }
    }
    cout << ans;
    return 0;
}