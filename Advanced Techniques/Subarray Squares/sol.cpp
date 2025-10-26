/**
 *    author:  Hakunaaa
 *    created: 26.10.2025 22:01:39
**/
#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
struct Line {
	mutable int k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(int x) const { return p < x; }
};
 
// queries for maximum
// if we want minimum then make minimum = true
bool minimum = true;
struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const int inf = LONG_MAX;
	int div(int a, int b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	// y = m*x+c; x wiint be the query parameter used later
	void add(int m, int c) {
	    if( minimum ){
            m=-m;
            c=-c;
	    }
		auto z = insert({m, c, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	int get(int x) {
		assert(!empty());
		auto l = *lower_bound(x);
		if( minimum ) return -(l.k * x + l.m);
		return l.k * x + l.m;
	}
};
 
const int N = 3005;
int s[N], dp[N][N];
 
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, K; cin >> n >> K;
    for(int i = 1; i <= n; i++) {
        int a; cin >> a;
        s[i] = s[i - 1] + a;
    }
    for(int i = 1; i <= n; i++) dp[1][i] = s[i] * s[i];
    for(int k = 2; k <= K; k++) {
        LineContainer solver;
        for(int i = 1; i <= n; i++) {
            if(i < k - 1) continue;
            if(i >= k) dp[k][i] = solver.get(s[i]) + s[i] * s[i];
            solver.add(-2 * s[i], dp[k - 1][i] + s[i] * s[i]);
        }
    }
    cout << dp[K][n];
    return 0;
}
