/**
 *    author:  Hakunaaa
 *    created: 31.10.2025 22:11:33
**/
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
using cd = complex<double>;
const double PI = acos(-1);
 
int reverse(int num, int lg_n) {
    int res = 0;
    for (int i = 0; i < lg_n; i++) {
        if (num & (1 << i))
            res |= 1 << (lg_n - 1 - i);
    }
    return res;
}
 
void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n)
        lg_n++;
 
    for (int i = 0; i < n; i++) {
        if (i < reverse(i, lg_n))
            swap(a[i], a[reverse(i, lg_n)]);
    }
 
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
 
    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}
 
vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
 
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);
 
    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}
 
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int k, n, m; cin >> k >> n >> m;
    vector<int> a(k + 1, 0), b(k + 1, 0), c;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[x] += 1;
    }
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        b[x] += 1;
    }
    c = multiply(a, b);
    for(int i = 2; i <= 2 * k; i++) cout << c[i] << ' ';
    return 0;
}