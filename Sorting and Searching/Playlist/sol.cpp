/**
 *    author:  Hakunaaa
 *    created: 18.09.2025 23:29:17
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, ans = 1, l = 1; cin >> n;
    vector<int> v(n + 1);
    map<int, int> mp;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        if(mp[v[i]]) {
            ans = max(ans, i - max(l, mp[v[i]] + 1) + 1);
            l = max(l, mp[v[i]] + 1);
        } else ans = max(ans, i - l + 1);
        mp[v[i]] = i;
    }
    cout << ans;
    return 0;
}