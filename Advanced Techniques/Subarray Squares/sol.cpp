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
 
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n; 
    vector<int> a(n), b(n), dp(n);
    for(int &el : a) cin >> el;
    for(int &el : b) cin >> el;
    int x = b[0];
    LineContainer solver;
    dp[0] = x * a[0];
    for(int i = 0; i < n; i++) {
        if(i) dp[i] = min(solver.get(a[i]), x * a[i]);
        solver.add(b[i], dp[i]);
    }
    cout << min(dp[n - 1], x * a[n - 1]);
    return 0;
}
