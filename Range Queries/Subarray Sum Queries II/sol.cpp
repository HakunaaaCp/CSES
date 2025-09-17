/**
 *    author:  Hakunaaa
 *    created: 17.09.2025 16:04:29
**/
#include <bits/stdc++.h>
#define int long long
using namespace std;

struct segtree {
    int n;
    vector<int> a, lo, hi;
    vector<array<int, 4>> t;
    segtree(vector<int> a) : a(a) {
        n = a.size();
        lo.resize(4 * n);
        hi.resize(4 * n);
        t.resize(4 * n);
        build(1, 0, n - 1);
    } 
    array<int, 4> combine(array<int, 4> a, array<int, 4> b) {
        return {a[0]+ b[0], max(a[1], a[0] + b[1]), max(b[2], a[2] + b[0]), max(max(a[3], b[3]), a[2] + b[1])};
    }
    void build(int u, int l, int r) {
        lo[u] = l, hi[u] = r;
        if(l == r) {
            t[u][0] = a[l];
            for(int i = 1; i < 4; i++) t[u][i] = max(a[l], 0LL);
            return;
        }
        int m = (l + r) / 2;
        build(u * 2, l, m);
        build(u * 2 + 1, m + 1, r);
        t[u] = combine(t[u * 2], t[u * 2 + 1]);
    }
    array<int, 4> get(int u, int a, int b) {
        int l = lo[u], r = hi[u];
        if(l == a && r == b) return t[u];
        int m = (l + r) / 2;
        if(b <= m) return get(u * 2, a, b);
        else if(a > m) return get(u * 2 + 1, a, b);
        else return combine(get(u * 2, a, m), get(u * 2 + 1, m + 1, b));
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> v(n);
    for(int &el : v) cin >> el;
    segtree T(v);
    while(q--) {
        int l, r; cin >> l >> r;
        l -= 1, r -= 1;
        cout << (T.get(1, l, r))[3] << '\n';
    }
    return 0;
}