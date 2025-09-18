/**
 *    author:  Hakunaaa
 *    created: 18.09.2025 21:44:46
**/
#include <bits/stdc++.h>
using namespace std;

struct segtree {
    int n;
    vector<int> a, t, lo, hi;
    segtree(vector<int> a) : a(a) {
        n = a.size();
        t.resize(4 * n);
        lo.resize(4 * n);
        hi.resize(4 * n);
        build(1, 0, n - 1);
    }
    void build(int u, int l, int r) {
        lo[u] = l, hi[u] = r;
        if(l == r) {
            t[u] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(u * 2, l, m);
        build(u * 2 + 1, m + 1, r);
        t[u] = min(t[u * 2], t[u * 2 + 1]);
    }
    int get(int u, int a, int b) {
        int l = lo[u], r = hi[u];
        if(l == a && r == b) return t[u];
        int m = (l + r) / 2;
        if(b <= m) return get(u * 2, a, b);
        else if(a > m) return get(u * 2 + 1, a, b);
        else return min(get(u * 2, a, m), get(u * 2 + 1, m + 1, b));
    }
    void up(int u, int pos, int val) {
        int l = lo[u], r = hi[u];
        if(l == r) {
            assert(l == pos);
            t[u] = val;
            return;
        }
        int m = (l + r) / 2;
        if(pos <= m) up(u * 2, pos, val);
        else up(u * 2 + 1, pos, val);
        t[u] = min(t[u * 2], t[u * 2 + 1]);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> v(n), p(n, 1e9);
    unordered_map<int, set<int>> mp; 
    for(int i = 0; i < n; i++) {
        cin >> v[i];
        mp[v[i]].insert(i);
    }
    for(auto [val, s] : mp) {
        int pr = -1;
        for(auto el : s) {
            if(pr != -1) p[pr] = el;
            pr = el;
        }
    }
    segtree T(p);
    while(q--) {
        int t, l, r; cin >> t >> l >> r;
        if(t == 1) {
            l -= 1; 
            if(v[l] == r) continue;
            auto it = mp[v[l]].find(l);
            int f = (it != mp[v[l]].begin() ? *prev(it) : -1);
            int s = (next(it) != mp[v[l]].end() ? *next(it) : -1);
            if(f != -1) {
                if(s != -1) p[f] = s;
                else p[f] = 1e9;
                T.up(1, f, p[f]);
            }
            mp[v[l]].erase(l);
            mp[r].insert(l);
            it = mp[r].find(l);
            f = (it != mp[r].begin() ? *prev(it) : -1);
            s = (next(it) != mp[r].end() ? *next(it) : -1);
            if(f != -1) {
                p[f] = l;
                T.up(1, f, p[f]);
            }
            p[l] = (s != -1 ? s : 1e9);
            T.up(1, l, p[l]);
            v[l] = r;
        } else {
            l -= 1, r -= 1;
            int m = T.get(1, l, r);
            cout << (m > r ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}