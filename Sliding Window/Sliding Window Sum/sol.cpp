/**
 *    author:  Hakunaaa
 *    created: 05.11.2025 23:37:23
**/
#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, k; cin >> n >> k;
    vector<int> v(n);
    int x, a, b, c; cin >> x >> a >> b >> c;
    v[0] = x;
    int f = x;
    for(int i = 1; i < n; i++) {
        v[i] = (a * v[i - 1] + b) % c;
        if(i < k) f += v[i];
    }
    int ans = f;
    for(int i = k; i < n; i++) {
        f -= v[i - k] - v[i];
        ans ^= f;
    }
    cout << ans;
    return 0;
}