/**
 *    author:  Hakunaaa
 *    created: 16.09.2025 16:34:17
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    vector<bool> vis(n + 1, false);
    for(int i = 0; i < n - 1; i++) {
        int a; cin >> a;
        vis[a] = 1;
    }
    int mis = -1;
    for(int i = 1; i <= n; i++) if(!vis[i]) mis = i;
    cout << mis;
    return 0;
}