/**
 *    author:  Hakunaaa
 *    created: 31.10.2025 18:49:29
**/
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    vector<int> sum(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        int a; cin >> a;
        sum[i] = sum[i - 1] + a;
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, LONG_MAX)), pos(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) pos[i][i] = i, dp[i][i] = 0;
    for(int i = n - 1; i >= 1; i--) {
        for(int j = i + 1; j <= n; j++) {
            int mn = LONG_MAX, c = sum[j] - sum[i - 1];
            for(int k = pos[i][j - 1]; k <= min(j - 1, pos[i + 1][j]); k++) {
                if(c + dp[i][k] + dp[k + 1][j] < mn) {
                    mn = c + dp[i][k] + dp[k + 1][j];
                    pos[i][j] = k;
                }
            }
            dp[i][j] = mn;
        }
    }
    cout << dp[1][n];
    return 0;
}